#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Get a number from stdin. */
static int get_num() {
	int ret;
	scanf("%d", &ret);
	return ret;
}

/* Setup random seed. */
static void setup_rand() {
	srand(time(NULL));
}

/* Get a random value from 0 to x-1. */
static int get_rand(int x) {
	int partition = RAND_MAX / x;
	int res;

	do res = rand() / partition;
	while (res < 0 || res >= x);
	/* printf("x = %d\n", res); */

	return res;
}

/* Explain the game. */
static void explain() {
	fputs("This is a probability name for algebra mid-term assessment.\n"
	      "\n"
	      "At first, there will a random coin picked from 4 irregular "
	      "coins, with the possibility of getting a head being 0/3, 1/3, "
	      "2/3, 3/3, respectively. The possibilities of getting each of "
	      "the 4 coins are the same.\n"
	      "\n"
	      "Then, you will be presented with three flipping from the picked "
	      "coin. You will have to guess which coin it is from the result.\n",
	      stderr
	);
}

/* Play the game for one round. */
static void play() {
	/* 0 means 0/3, etc. */
	int coin = get_rand(4);

	fputs("The results:\n", stderr);
	for (int i = 0; i < 3; i++) {
		int res = get_rand(3);
		if (res < coin)
			puts("H");
		else
			puts("T");
	}

	fputs("Your guess (0 for 0/3, 1 for 1/3, and so on): ", stderr);
	int guess = get_num();

	if (guess == coin)
		fputs("You win!\n", stderr);
	else
		fprintf(stderr, "You lose. It's actually %d/3.\n", coin);
	system("pause");
}

int main() {
	explain();
	system("pause");
	setup_rand();
	while (true)
		play();
	return EXIT_SUCCESS;
}
