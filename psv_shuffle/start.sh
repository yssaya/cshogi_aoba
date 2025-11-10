export LD_LIBRARY_PATH=/home/yss/tensorrt/trt10.10.0.31_cuda_11.8/lib:$LD_LIBRARY_PATH

#python3 psv_re_eval.py ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5340981_126_shuffle.bin hoge.hcpe
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5340981_126_shuffle.bin hogepsvads.aaa

#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5606850_000_126_shuffle_q.bin 5606850_000_126_shuffle_q_dr2.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5340981_000_125_shuffle_q.bin 5340981_000_125_shuffle_q_dr2.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5872823_000_126_shuffle_q.bin 5872823_000_126_shuffle_q_dr2.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6181115_000_126_shuffle_q.bin 6181115_000_126_shuffle_q_dr2.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6446725_000_126_shuffle_q.bin 6446725_000_126_shuffle_q_dr2.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6712082_000_126_shuffle_q.bin 6712082_000_126_shuffle_q_dr2.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6977931_000_126_shuffle_q.bin 6977931_000_126_shuffle_q_dr2.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/7275299_000_126_shuffle_q.bin 7275299_000_126_shuffle_q_dr2.bin


#python3 ~/shogi/dlshogi_20250403/dlshogi/utils/hcpe_re_eval.py /home/yss/shogi/dlshogi_dr2_exhi/model/model-dr2_exhi.onnx ~/shogi/dlshogi_hcpe/floodgate_2019-2021_r3500-001.hcpe ./hoge.abc

#./psvs ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5340981_000_125_shuffle.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5606850_000_126_shuffle.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5872823_000_126_shuffle.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6181115_000_126_shuffle.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6446725_000_126_shuffle.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6712082_000_126_shuffle.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6977931_000_126_shuffle.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/7275299_000_126_shuffle.bin
#./psvs ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5340981_000_125_shuffle_q.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5606850_000_126_shuffle_q.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5872823_000_126_shuffle_q.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6181115_000_126_shuffle_q.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6446725_000_126_shuffle_q.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6712082_000_126_shuffle_q.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6977931_000_126_shuffle_q.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/7275299_000_126_shuffle_q.bin
#./psvs 5606850_000_126_shuffle_q_dr2.bin 5340981_000_125_shuffle_q_dr2.bin 5872823_000_126_shuffle_q_dr2.bin 6181115_000_126_shuffle_q_dr2.bin 6446725_000_126_shuffle_q_dr2.bin 6712082_000_126_shuffle_q_dr2.bin 6977931_000_126_shuffle_q_dr2.bin 7275299_000_126_shuffle_q_dr2.bin

#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx /home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/5340981_126_shuffle.bin ./hoge.abc

#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5606850_000_126_shuffle_q.bin 5606850_000_126_shuffle_q_aoba.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5340981_000_125_shuffle_q.bin 5340981_000_125_shuffle_q_aoba.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5872823_000_126_shuffle_q.bin 5872823_000_126_shuffle_q_aoba.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6181115_000_126_shuffle_q.bin 6181115_000_126_shuffle_q_aoba.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6446725_000_126_shuffle_q.bin 6446725_000_126_shuffle_q_aoba.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6712082_000_126_shuffle_q.bin 6712082_000_126_shuffle_q_aoba.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6977931_000_126_shuffle_q.bin 6977931_000_126_shuffle_q_aoba.bin
#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/7275299_000_126_shuffle_q.bin 7275299_000_126_shuffle_q_aoba.bin

#python3 psv_re_eval.py --tensorrt /home/yss/shogi/dlshogi_20250403/model/20250407_235846_model_resnet30x384_relu_060.onnx ~/shogi/dlshogi_hcpe/shogi_hao_depth9/7275299_000_126_shuffle_q.bin.1 7275299_000_126_shuffle_q_aoba.bin.1

#./psvs ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5340981_000_125_shuffle_q_aoba.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5606850_000_126_shuffle_q_aoba.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/5872823_000_126_shuffle_q_aoba.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6181115_000_126_shuffle_q_aoba.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6446725_000_126_shuffle_q_aoba.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6712082_000_126_shuffle_q_aoba.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/6977931_000_126_shuffle_q_aoba.bin ~/shogi/dlshogi_hcpe/shogi_hao_depth9/7275299_000_126_shuffle_q_aoba.bin
#./psvs /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/8_seq_q.bin /home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/8_seq_q_aoba.bin

#./psvs /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/5340981_000_125_shuffle_q_dr2.bin /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/5606850_000_126_shuffle_q_dr2.bin /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/5872823_000_126_shuffle_q_dr2.bin /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/6181115_000_126_shuffle_q_dr2.bin /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/6446725_000_126_shuffle_q_dr2.bin /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/6712082_000_126_shuffle_q_dr2.bin /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/6977931_000_126_shuffle_q_dr2.bin /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/7275299_000_126_shuffle_q_dr2.bin

#./psvs /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/8_seq_q.bin /media/yss/old/home/yss/shogi/dlshogi_hcpe/shogi_hao_depth9/8_seq_q_aoba_a600.bin
./psvs ~/shogi/dlshogi_hcpe/shogi_hao_depth9/8_seq_q_aoba.bin
