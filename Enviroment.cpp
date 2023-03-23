struct TrainingUnit
{
	int state = 0;
	int action = 0;
	int reward = 0;
	int new_state = 0;
	bool done = false;
};

class Env
{
public:
	static const int height = 10;
	static const int width = 10;
	int state_count = height*width;
	static const int action_count = 4;

	Env() {
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++)
				grid[i][j] = ( ((rand()%1000)*0.001) < wall_chance) ? 1 : 0;
		grid[0][0] = 0;
		grid[width-1][height-1] = 0;
	}

	TrainingUnit reset() {
		pos_x = 0;
		pos_y = 0;
		done = false;
		TrainingUnit train_u;
		return train_u;
	}

	TrainingUnit step(int action)
	{
		TrainingUnit train_u;
		train_u.state = width * pos_y + pos_x;
		train_u.action = action;

		int new_x = pos_x;
		int new_y = pos_y;
		if (action == 0) new_x--;
		else if (action == 1) new_x++;
		else if (action == 2) new_y--;
		else if (action == 3)  new_y++;
		if (new_x > width-1 || new_x < 0 ||
			new_y > height-1 || new_y < 0 ||
			grid[new_x][new_y]) {
			train_u.reward--;
		} else {
			pos_x = new_x;
			pos_y = new_y;
		}

		done = (pos_x == end_x && pos_y == end_y);
		train_u.reward = done ? 1 : 0;
		train_u.new_state = width * pos_y + pos_x;
		train_u.done = done;
		return train_u;
	}

	int random_action() {
		return rand()%action_count;
	}

	void render() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (pos_y == i && pos_x == j)
					std::cout << ":D";
				else if (end_y == i && end_x == j)
					std::cout << "69";
				else if (!grid[i][j])
					std::cout << "  ";
				else
					std::cout << " #";
			}
			std::cout << "\n";
		}
	}

private:
	int grid[width][height];
	int pos_x = 0;
	int pos_y = 0;
	int end_x = width-1;
	int end_y = height-1;
	int actions[action_count] = {0, 1, 2, 3};
	float wall_chance = 0.1;
	bool done = false;
};
