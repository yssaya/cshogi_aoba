from gym.envs.registration import register

register(
    id='Shogi-v0',
    entry_point='cshogi_aoba.gym_shogi.envs:ShogiEnv',
)