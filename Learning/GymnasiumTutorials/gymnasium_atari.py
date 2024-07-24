import gymnasium as gym
import time

env = gym.make("BreakoutNoFrameskip-v4", render_mode="human")

print("Observation Space: ", env.observation_space)
print("Action Space       ", env.action_space)


obs = env.reset()

for i in range(1000):
    action = env.action_space.sample()
    obs, reward, done, truncated, info = env.step(action)
    env.render()
    time.sleep(0.01)
env.close()

