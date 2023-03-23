class Agent
{
public:
	Agent(int state_count, int action_count)
	{
		for (int j = 0; j < state_count; j++) {
			std::vector<float> new_line;
			for (int i = 0; i < action_count; i++)
				new_line.push_back((rand()%1000)*0.001);
			qtable.push_back(new_line);
		}
	}

	void train(Env* env)
	{
		std::vector<int> steps_store;
		for (int i = 0; i < epochs; i++)
		{
			TrainingUnit train_u = env->reset();
			int state = train_u.state;
			int reward = train_u.reward;
			bool done = train_u.done;
			int steps = 0;
			int action = 0;

			while(!done)
			{
				steps++;
				if ((rand()%1000)*0.001 < epsilon)
					action = env->random_action();
				else
					action = best_action(state);

				train_u = env->step(action);
				int new_state = train_u.new_state;
				reward = train_u.reward;
				done = train_u.done;

				// Update QTable value with Bellman equation
				qtable[state][action] = reward + gamma * max_reward(new_state);

				state = new_state;
			}
			// The more we learn the less whe take random actions
			epsilon -= decay * epsilon;

			if (i % 50 == 0 || i >= epochs-1) {
				env->render();
				std::cout << "Epoch: " << i+1 << '/' << epochs << std::endl;
				std::cout << "Done in " << steps << " steps." << std::endl;
				std::cout << "---------------------------------" << std::endl;
			}
			steps_store.push_back(steps);
		}
		/*
		for (auto s : steps_store)
			std::cout << s << std::endl;
		*/
	}
private:
	int epochs = 1000;
	float gamma = 0.1;
	float epsilon = 0.8;
	float decay = 0.01;
	std::vector<std::vector<float>> qtable;

	float max_reward(int state) {
		std::vector<float> line = qtable[state];
		return *std::max_element(line.begin(), line.end());;
	}
	int best_action(int state) {
		std::vector<float> line = qtable[state];
		return std::distance(line.begin(), std::max_element(line.begin(), line.end()));
	}
};
