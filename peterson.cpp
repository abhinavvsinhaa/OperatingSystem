// Look for both the processes at the same time synchronously

// for process Pi
do {
	// process Pi wants to enter the critical section
	flag[i] = true;

	// but peterson solution being humble, provides the chance to Pj
	turn = j;

	while (flag[j] && turn == j);

	// critical section

	flag[i] = false;

	// remainder section

} while (true)

// ----------------------------------------

// for process Pj
do {
	// process Pj wants to enter the critical section
	flag[j] = true;

	// but peterson solution being humble, provides the chance to Pi
	turn = i;

	while (flag[i] && turn == i);

	// critical section

	flag[j] = false;

	// remainder section

} while (true)