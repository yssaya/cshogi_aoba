使い方
2025年のAobaZeroのdlshogiモデルを使って
 shogi_hao_depth9 のデータ(静止探索で動く局面は変換済み)の評価値のみを変更して
5606850_000_126_shuffle_q_aoba.bin というファイルで保存するには

$ python3 psv_re_eval.py --tensorrt ./20250407_235846_model_resnet30x384_relu_060.onnx ./shogi_hao_depth9/5606850_000_126_shuffle_q.bin 5606850_000_126_shuffle_q_aoba.bin

psv_re_eval.py の
AOBA = True  # False
を False で通常のdlshogiモデルになります。

psv_re_eval.py は hcpe_re_eval.py を修正して作成しています。
https://tadaoyamaoka.hatenablog.com/entry/2024/12/30/123302

psvs.cpp は *.bin を結合したりシャッフルしたり勝率変換定数を756から600に変更したりします。
main()とか start.sh を見てください。

shogi_hao_depth9 はファイル数が多いので、128 x 8分割されたものをまとめて、
300GBの1個のデータとして使っています。
テスト用には 128 x 8 個のファイルの1つだけを使ってます。

