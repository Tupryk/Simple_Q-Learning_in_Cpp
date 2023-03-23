#include <iostream>
#include <vector>
#include "Enviroment.cpp"
#include "Agent.cpp"

int main() {
	srand( time( NULL ) );
	Env env;
	Agent agent(env.state_count, env.action_count);
	agent.train(&env);
	return 0;
}
