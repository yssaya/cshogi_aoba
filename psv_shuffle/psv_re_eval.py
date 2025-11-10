import onnxruntime
import argparse
import time
import numpy as np
AOBA = True  # False
if AOBA:
    from cshogi_aoba import *
    from cshogi_aoba.dlshogi import make_input_features, FEATURES1_NUM, FEATURES2_NUM
else:
    from cshogi import *
    from cshogi.dlshogi import make_input_features, FEATURES1_NUM, FEATURES2_NUM

parser = argparse.ArgumentParser()
parser.add_argument('model')
parser.add_argument('psv')
parser.add_argument('psv_out')
parser.add_argument('--a', type=float, default=756.0864962951762)
parser.add_argument('--alpha', type=float, default=1)
parser.add_argument('--batch_size', '-b', type=int, default=1024)
parser.add_argument('--tensorrt', action='store_true')
args = parser.parse_args()

alpha = args.alpha
a = args.a
batch_size = args.batch_size
psvs = np.fromfile(args.psv, dtype=PackedSfenValue)
psvs_size = len(psvs)
print(f'input num = {psvs_size}')
f_out = open(args.psv_out, 'wb')

#psv_outs = np.zeros(len(psvs), PackedSfenValue)
#hcps = np.zeros(len(psvs), HuffmanCodedPos)

session = onnxruntime.InferenceSession(args.model, providers=['TensorrtExecutionProvider', 'CUDAExecutionProvider', 'CPUExecutionProvider'] if args.tensorrt else ['CUDAExecutionProvider', 'CPUExecutionProvider'])
x1 = np.empty((batch_size, FEATURES1_NUM, 9, 9), dtype=np.float32)
x2 = np.empty((batch_size, FEATURES2_NUM, 9, 9), dtype=np.float32)

def evaluate_and_write(indexes, start_index, end_index):
    io_binding = session.io_binding()
    io_binding.bind_cpu_input('input1', x1[:len(indexes)])
    io_binding.bind_cpu_input('input2', x2[:len(indexes)])
    io_binding.bind_output('output_policy')
    io_binding.bind_output('output_value')
    session.run_with_iobinding(io_binding)
    _, values = io_binding.copy_outputs_to_cpu()

    scores = value_to_score(values.reshape(-1), a)
    #out_hcpes = hcpes[start_index:end_index + 1].copy()
    out_psvs = psvs[start_index:end_index + 1].copy()
    if alpha == 1:
        out_psvs['score'][[i - start_index for i in indexes]] = scores
    else:
        indexes = [i - start_index for i in indexes]
        out_psvs['score'][indexes] = (1 - alpha) * out_psvs['score'][indexes] + alpha * scores

    if i < batch_size:
        for n in range(len(out_psvs)):
            psv   = psvs[n + start_index]
            o_psv = out_psvs[n]
            print(f"i={i:7},n={n:4},score={psv['score']:6}, -> {o_psv['score']:6}, turn={psv['gamePly']&1}, gamePly={psv['gamePly']:3},move={psv['move']:6},result={psv['game_result']:2}")
            if n > 40: break
    #out_hcpes.tofile(f_out)
    out_psvs.tofile(f_out)

def value_to_score(values, a):
    scores = np.empty_like(values)
    # boolean indexing. It is processed in bulk (vectorized)
    scores[values == 1] =  30000
    scores[values == 0] = -30000
    mask = (values != 1) & (values != 0)
    scores[mask] = -a * np.log(1 / values[mask] - 1)
    scores = np.clip(scores, -30000, 30000)
    return scores


t_start = time.perf_counter()
board = Board()
i = 0
j = 0
indexes = []
start_index = 0
for psv in psvs:
    #if abs(psv['score']) > limit_eval:
    #    continue
    #if limit_moves is not None and psv['gamePly'] > limit_moves:
    #    continue
    if board.set_psfen(psv['sfen']) == False:
        print('illegal data:', psv)
        exit(0)
    #print(f"sfen={psv['sfen']}")
    if i < 20:
        #print(board)
        #print(board.sfen())
        print(f"i={i:7},score={psv['score']:6},gamePly={psv['gamePly']:3},move={psv['move']:6},result={psv['game_result']:2},turn={board.turn}")
    if board.is_ok() == False:
        print('illegal data', psv)
        exit(0)
    #board.to_hcp(np.asarray(hcps[i]))
    make_input_features(board, x1[j], x2[j])
    indexes.append(i)

    if j == batch_size - 1 or i == psvs_size - 1:
        evaluate_and_write(indexes, start_index, i)
        j = 0
        indexes.clear()
        start_index = i + 1
    else:
        j += 1

    #psv_outs[i] = psv
    i += 1
    if (i%100000) == 0:
        print(f'{i:7}',end=',',flush=True)
        if (i%1000000) == 0:
            print(f'')

#hcps[:i].tofile(args.hcp)
#psv_outs[:i].tofile(args.psv_out)
t_end = time.perf_counter()
print(f'')
print(f'time (min)= {(t_end-t_start)/60}')
print(f'output num = {i}')
