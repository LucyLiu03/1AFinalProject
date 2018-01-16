/*
char w[10]={'e','w','w','w','w','w','w','w','w','w'};
char r[10]={'e','r','r','r','r','r','r','r','r','r'};
char b[10]={'e','b','b','b','b','b','b','b','b','b'};
char o[10]={'e','o','o','o','o','o','o','o','o','o'};
char g[10]={'e','g','g','g','g','g','g','g','g','g'};
char y[10]={'e','y','y','y','y','y','y','y','y','y'};
*/

char w[10]={'e','e','e','e','e','e','e','e','e','e'};
char r[10]={'e','e','e','e','e','e','e','e','e','e'};
char b[10]={'e','e','e','e','e','e','e','e','e','e'};
char o[10]={'e','e','e','e','e','e','e','e','e','e'};
char g[10]={'e','e','e','e','e','e','e','e','e','e'};
char y[10]={'e','e','e','e','e','e','e','e','e','e'};

void flopArm(bool direction)//HIGHER MAX ANGLE
{
	int ENC_LIMIT=0;
	nMotorEncoder[motorC]=0;
	if (direction)
	{
		ENC_LIMIT = 120;
		motor[motorC]=25;
	}
	else
	{
		ENC_LIMIT = 121;
		motor[motorC]=-25;
	}
	while (abs(nMotorEncoder[motorC])<ENC_LIMIT&&(!SensorValue[S4]))
	{}
	motor[motorC]=0;
	wait1Msec(500);
}

void flop(int numTimes)
{
	for (int i=0; i<numTimes; i++)
	{
		flopArm(1);
		flopArm(0);
	}
}

void tray(bool direction)
{
	const int ENC_LIMIT_ROTATE=105;
	const int ENC_LIMIT_ADJUST=15;
	nMotorEncoder[motorA]=0;
	if (!direction)
		motor[motorA]=10;
	else
		motor[motorA]=-10;
	while(abs(nMotorEncoder[motorA])<ENC_LIMIT_ROTATE&&(!SensorValue[S4]))
	{}

	if (!direction)
		motor[motorA]=-10;
	else
		motor[motorA]=10;
	nMotorEncoder[motorA]=0;
	while(abs(nMotorEncoder[motorA])<ENC_LIMIT_ADJUST&&(!SensorValue[S4]))
	{}
	motor[motorA]=0;
	wait1Msec(300);
}

void orient(char face)
{
	if (face=='r')
		flop(1);
	else if (face=='o')
		flop(3);
	else if (face=='b')
	{
		tray(1);
		flop(1);
	}
	else if (face=='g')
	{
		tray(0);
		flop(1);
	}
	else if (face=='y')
	{}
	else if (face=='w')
		flop(2);
}

void invOrient(char face)//FROM NATURE OF ROTATION FUNCTIONS, INVORIENTS START WITH A FLOP FOR FREE
{
	if (face =='r')
		flop(2);
	else if (face=='o')//DELETE IF UNNECESSARY
	{}
	else if (face=='b')
	{
		flop(2);
		tray(0);
	}
	else if (face=='g')
	{
		flop(2);
		tray(1);
	}
	else if (face=='w')
		flop(1);
	else
		flop(3);
}

void swap(char & a, char & b)
{
	char temp=' ';
	temp=a;
	a=b;
	b=temp;
}

void rotate(char face, bool direction)
{
	orient(face);
	flopArm(1);
	tray(!direction);
	flopArm(0);
	invOrient(face);

	if (face=='w')
	{
		if (direction)
		{
			swap(r[1], b[1]);
			swap(r[2], b[2]);
			swap(r[3], b[3]);

			swap(o[1], b[1]);
			swap(o[2], b[2]);
			swap(o[3], b[3]);

			swap(o[1], g[1]);
			swap(o[2], g[2]);
			swap(o[3], g[3]);

			swap(w[1], w[7]);
			swap(w[7], w[9]);
			swap(w[9], w[3]);

			swap(w[2], w[4]);
			swap(w[4], w[8]);
			swap(w[8], w[6]);
		}

		else
		{
			swap(r[1], g[1]);
			swap(r[2], g[2]);
			swap(r[3], g[3]);

			swap(o[1], g[1]);
			swap(o[2], g[2]);
			swap(o[3], g[3]);

			swap(o[1], b[1]);
			swap(o[2], b[2]);
			swap(o[3], b[3]);

			swap(w[1], w[3]);
			swap(w[3], w[9]);
			swap(w[9], w[7]);

			swap(w[2], w[6]);
			swap(w[6], w[8]);
			swap(w[8], w[4]);
		}
	}

	else if (face=='r')
	{
		if (direction)
		{
			swap(y[7], b[1]);
			swap(y[8], b[4]);
			swap(y[9], b[7]);

			swap(w[7], b[1]);
			swap(w[8], b[4]);
			swap(w[9], b[7]);

			swap(w[7], g[9]);
			swap(w[8], g[6]);
			swap(w[9], g[3]);

			swap(r[1], r[7]);
			swap(r[7], r[9]);
			swap(r[9], r[3]);

			swap(r[2], r[4]);
			swap(r[4], r[8]);
			swap(r[8], r[6]);

		}

		else
		{
			swap(y[7], g[9]);
			swap(y[8], g[6]);
			swap(y[9], g[3]);

			swap(w[7], g[9]);
			swap(w[8], g[6]);
			swap(w[9], g[3]);

			swap(w[7], b[1]);
			swap(w[8], b[4]);
			swap(w[9], b[7]);

			swap(r[1], r[3]);
			swap(r[3], r[9]);
			swap(r[9], r[7]);

			swap(r[2], r[6]);
			swap(r[6], r[8]);
			swap(r[8], r[4]);
		}
	}

	else if (face=='b')
	{
		if (direction)
		{
			swap(y[1], o[1]);
			swap(y[4], o[4]);
			swap(y[7], o[7]);

			swap(o[1], w[9]);
			swap(o[4], w[6]);
			swap(o[7], w[3]);

			swap(w[3], r[3]);
			swap(w[6], r[6]);
			swap(w[9], r[9]);

			swap(b[1], b[7]);
			swap(b[7], b[9]);
			swap(b[9], b[3]);

			swap(b[2], b[4]);
			swap(b[4], b[8]);
			swap(b[8], b[6]);
		}

		else
		{
			swap(y[1], r[9]);
			swap(y[4], r[6]);
			swap(y[7], r[3]);

			swap(w[3], r[3]);
			swap(w[6], r[6]);
			swap(w[9], r[9]);

			swap(w[3], o[7]);
			swap(w[6], o[4]);
			swap(w[9], o[1]);

			swap(b[1], b[3]);
			swap(b[3], b[9]);
			swap(b[9], b[7]);

			swap(b[2], b[6]);
			swap(b[6], b[8]);
			swap(b[8], b[4]);
		}
	}

	else if (face=='o')
	{
		if (direction)
		{
			swap(g[1], y[3]);
			swap(g[4], y[2]);
			swap(g[7], y[1]);

			swap(g[1], w[3]);
			swap(g[4], w[2]);
			swap(g[7], w[1]);

			swap(w[1], b[3]);
			swap(w[2], b[6]);
			swap(w[3], b[9]);

			swap(o[1], o[7]);
			swap(o[7], o[9]);
			swap(o[9], o[3]);

			swap(o[2], o[4]);
			swap(o[4], o[8]);
			swap(o[8], o[6]);
		}

		else
		{
			swap(y[1], b[3]);
			swap(y[2], b[6]);
			swap(y[3], b[9]);

			swap(w[1], b[3]);
			swap(w[2], b[6]);
			swap(w[3], b[9]);

			swap(w[1], g[7]);
			swap(w[2], g[4]);
			swap(w[3], g[1]);

			swap(o[1], o[3]);
			swap(o[3], o[9]);
			swap(o[9], o[7]);

			swap(o[2], o[6]);
			swap(o[6], o[8]);
			swap(o[8], o[4]);
		}
	}

	else if (face=='g')
	{
		if (direction)
		{
			swap(r[1], y[9]);
			swap(r[4], y[6]);
			swap(r[7], y[3]);

			swap(r[1], w[1]);
			swap(r[4], w[4]);
			swap(r[7], w[7]);

			swap(w[1], o[9]);
			swap(w[4], o[6]);
			swap(w[7], o[3]);

			swap(g[1], g[7]);
			swap(g[7], g[9]);
			swap(g[9], g[3]);

			swap(g[2], g[4]);
			swap(g[4], g[8]);
			swap(g[8], g[6]);
		}

		else
		{
			swap(y[3], o[3]);
			swap(y[6], o[6]);
			swap(y[9], o[9]);

			swap(w[1], o[9]);
			swap(w[4], o[6]);
			swap(w[7], o[3]);

			swap(w[1], r[1]);
			swap(w[4], r[4]);
			swap(w[7], r[7]);

			swap(g[1], g[3]);
			swap(g[3], g[9]);
			swap(g[9], g[7]);

			swap(g[2], g[6]);
			swap(g[6], g[8]);
			swap(g[8], g[4]);
		}
	}

	else if (face=='y')
	{
		if (direction)
		{
			swap(r[7], g[7]);
			swap(r[8], g[8]);
			swap(r[9], g[9]);

			swap(o[7], g[7]);
			swap(o[8], g[8]);
			swap(o[9], g[9]);

			swap(o[7], b[7]);
			swap(o[8], b[8]);
			swap(o[9], b[9]);

			swap(y[1], y[7]);
			swap(y[7], y[9]);
			swap(y[9], y[3]);

			swap(y[2], y[4]);
			swap(y[4], y[8]);
			swap(y[8], y[6]);
		}

		else
		{
			swap(r[7], b[7]);
			swap(r[8], b[8]);
			swap(r[9], b[9]);

			swap(o[7], b[7]);
			swap(o[8], b[8]);
			swap(o[9], b[9]);

			swap(o[7], g[7]);
			swap(o[8], g[8]);
			swap(o[9], g[9]);

			swap(y[1], y[3]);
			swap(y[3], y[9]);
			swap(y[9], y[7]);

			swap(y[2], y[6]);
			swap(y[6], y[8]);
			swap(y[8], y[4]);
		}
	}
}//perfect

void orientWhiteEdge(char colour)
{
	if (w[8]=='w'&&r[2]==colour)//white edge with white center
	{
		if (colour=='r')
		{}

		else if (colour=='b')
		{
			rotate('r', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('r', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('r', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('g', 1);
			rotate('g', 1);
		}
	}

	else if (w[6]=='w'&&b[2]==colour)
	{
		if (colour=='b')
		{}

		else if (colour=='o')
		{
			rotate('b', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('o', 1);
		}

		else if (colour=='r')
		{
			rotate('b', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='g')
		{
			rotate('b', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('g', 1);
		}
	}

	else if (w[2]=='w'&&o[2]==colour)
	{
		if (colour=='o')
		{}

		else if (colour=='g')
		{
			rotate('o', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('o', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('o', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('b', 1);
			rotate('b', 1);
		}
	}

	else if (w[4]=='w'&&g[2]==colour)
	{
		if (colour=='g')
		{}

		else if (colour=='r')
		{
			rotate('g', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('g', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('g', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('o', 1);
			rotate('o', 1);
		}
	}

	else if (r[2]=='w'&&w[8]==colour)//above but flipped
	{
		if (colour=='r')
		{
			rotate('r', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('r', 0);
			rotate('b', 0);
		}

		else if (colour=='b')
		{
			rotate('r', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('r', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('o', 1);
			rotate('b', 1);
		}

		else if (colour=='g')
		{
			rotate('r', 0);
			rotate('g', 0);
		}
	}

	else if (b[2]=='w'&&w[6]==colour)
	{
		if (colour=='b')
		{
			rotate('b', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('b', 0);
			rotate('o', 0);
		}

		else if (colour=='o')
		{
			rotate('b', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('b', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('g', 1);
			rotate('o', 1);
		}

		else if (colour=='r')
		{
			rotate('b', 0);
			rotate('r', 0);
		}
	}

	else if (o[2]=='w'&&w[2]==colour)
	{
		if (colour=='o')
		{
			rotate('o', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('o', 0);
			rotate('g', 0);
		}

		else if (colour=='g')
		{
			rotate('o', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('o', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('r', 1);
			rotate('g', 1);
		}

		else if (colour=='b')
		{
			rotate('o', 0);
			rotate('b', 0);
		}
	}

	else if (g[2]=='w'&&w[4]==colour)
	{
		if (colour=='g')
		{
			rotate('g', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('g', 0);
			rotate('r', 0);
		}

		else if (colour=='r')
		{
			rotate('g', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('g', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('b', 1);
			rotate('r', 1);
		}

		else if (colour=='o')
		{
			rotate('g', 0);
			rotate('r', 0);
		}
	}

	else if (r[6]=='w'&&b[4]==colour)//White facing red center layer two
	{
		if (colour=='r')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('o', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('r', 1);
			rotate('r', 1);
			rotate('g', 0);
			rotate('r', 1);
			rotate('r', 1);
		}
	}

	else if (r[4]=='w'&&g[6]==colour)
	{
		if (colour=='r')
		{
			rotate('g', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('r', 1);
			rotate('r', 1);
			rotate('b', 1);
			rotate('r', 1);
			rotate('r', 1);

		}

		else if (colour=='o')
		{
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('o', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('g', 0);
		}
	}

	else if (b[6]=='w'&&o[4]==colour)//White facing blue center layer two
	{
		if (colour=='b')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('b', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('g', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('b', 1);
			rotate('b', 1);
			rotate('r', 0);
			rotate('b', 1);
			rotate('b', 1);
		}
	}

	else if (b[4]=='w'&&r[6]==colour)
	{
		if (colour=='b')
		{
			rotate('r', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('b', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('b', 1);
			rotate('b', 1);
			rotate('o', 1);
			rotate('b', 1);
			rotate('b', 1);

		}

		else if (colour=='g')
		{
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('g', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('r', 0);
		}
	}

	else if (o[6]=='w'&&g[4]==colour)//White facing orange center layer two ERROR PRONE
	{
		if (colour=='o')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('o', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('o', 1);
			rotate('o', 1);
			rotate('b', 0);
			rotate('o', 1);
			rotate('o', 1);
		}
	}

	else if (o[4]=='w'&&b[6]==colour)
	{
		if (colour=='o')
		{
			rotate('b', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('o', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('o', 1);
			rotate('o', 1);
			rotate('g', 1);
			rotate('o', 1);
			rotate('o', 1);

		}

		else if (colour=='r')
		{
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('b', 0);
		}
	}

	else if (g[6]=='w'&&r[4]==colour)//White facing green center layer two ERROR PRONE
	{
		if (colour=='g')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('g', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('b', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('g', 1);
			rotate('g', 1);
			rotate('o', 0);
			rotate('g', 1);
			rotate('g', 1);
		}
	}

	else if (g[4]=='w'&&o[6]==colour)
	{
		if (colour=='g')
		{
			rotate('o', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('g', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('g', 1);
			rotate('g', 1);
			rotate('r', 1);
			rotate('g', 1);
			rotate('g', 1);

		}

		else if (colour=='b')
		{
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('b', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('o', 0);
		}
	}

	else if (y[8]=='w'&&r[8]==colour)//White facing yellow
	{
		if (colour=='r')
		{
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 1);
			rotate('b', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 0);
			rotate('g', 1);
			rotate('g', 1);
		}
	}

	else if (y[4]=='w'&&b[8]==colour)
	{
		if (colour=='b')
		{
			rotate('b', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 1);
			rotate('o', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 0);
			rotate('r', 1);
			rotate('r', 1);
		}
	}

	else if (y[2]=='w'&&o[8]==colour)
	{
		if (colour=='o')
		{
			rotate('o', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 1);
			rotate('g', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 0);
			rotate('b', 1);
			rotate('b', 1);
		}
	}

	else if (y[6]=='w'&&g[8]==colour)
	{
		if (colour=='g')//LEFT OFF HERE
		{
			rotate('g', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 1);
			rotate('r', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 0);
			rotate('o', 1);
			rotate('o', 1);
		}
	}

	else if (y[8]==colour&&r[8]=='w')//Above but flipped
	{
		if (colour=='r')
		{
			rotate('y', 0);
			rotate('g', 0);
			rotate('r', 1);
			rotate('g', 1);
		}

		else if (colour=='g')
		{
			rotate('r', 1);
			rotate('g', 0);
			rotate('r', 0);
		}

		else if (colour=='o')
		{
			rotate('y', 0);
			rotate('g', 1);
			rotate('o', 0);
			rotate('g', 0);
		}

		else if (colour=='b')
		{
			rotate('r', 0);
			rotate('b', 1);
			rotate('r', 1);
		}
	}

	else if (y[6]==colour&&g[8]=='w')
	{
		if (colour=='g')
		{
			rotate('y', 0);
			rotate('o', 0);
			rotate('g', 1);
			rotate('o', 1);
		}

		else if (colour=='o')
		{
			rotate('g', 1);
			rotate('o', 0);
			rotate('g', 0);
		}

		else if (colour=='b')
		{
			rotate('y', 0);
			rotate('o', 1);
			rotate('b', 0);
			rotate('o', 0);
		}

		else if (colour=='r')
		{
			rotate('g', 0);
			rotate('r', 1);
			rotate('g', 1);
		}
	}

	else if (y[2]==colour&&o[8]=='w')
	{
		if (colour=='o')
		{
			rotate('y', 0);
			rotate('b', 0);
			rotate('o', 1);
			rotate('b', 1);
		}

		else if (colour=='b')
		{
			rotate('o', 1);
			rotate('b', 0);
			rotate('o', 0);
		}

		else if (colour=='r')
		{
			rotate('y', 0);
			rotate('b', 1);
			rotate('r', 0);
			rotate('b', 0);
		}

		else if (colour=='g')
		{
			rotate('o', 0);
			rotate('g', 1);
			rotate('o', 1);
		}
	}

	else if (y[4]==colour&&b[8]=='w')
	{
		if (colour=='b')
		{
			rotate('y', 0);
			rotate('r', 0);
			rotate('b', 1);
			rotate('r', 1);
		}

		else if (colour=='r')
		{
			rotate('b', 1);
			rotate('r', 0);
			rotate('b', 0);
		}

		else if (colour=='g')
		{
			rotate('y', 0);
			rotate('r', 1);
			rotate('g', 0);
			rotate('r', 0);
		}

		else if (colour=='o')
		{
			rotate('b', 0);
			rotate('o', 1);
			rotate('b', 1);
		}
	}
}

void orientWhiteCorner(char colour)//colour is colour of piece below white right side
{
	if (w[9]=='w'&&b[1]==colour)//white face top white
	{
		if (colour=='b')
		{}

		else if (colour=='o')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}
	}//brw

	else if(w[3]=='w'&&o[1]==colour)
	{
		if (colour=='o')
		{}

		else if (colour=='g')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}
	}

	else if(w[1]=='w'&&g[1]==colour)
	{
		if (colour=='g')
		{}

		else if (colour=='r')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}
	}

	else if(w[7]=='w'&&r[1]==colour)
	{
		if (colour=='r')
		{}

		else if (colour=='b')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}
	}

	else if(g[3]=='w'&&w[7]==colour)//white face bottom left white
	{
		if (colour=='r')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}
	}//brw

	else if(r[3]=='w'&&w[9]==colour)
	{
		if (colour=='b')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}
	}

	else if(b[3]=='w'&&w[3]==colour)
	{
		if (colour=='o')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}
	}

	else if(o[3]=='w'&&w[1]==colour)
	{
		if (colour=='g')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}
	}

	else if (b[1]=='w'&&r[3]==colour)//white face bottom right white
	{
		if (colour=='b')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}
	}

	else if (o[1]=='w'&&b[3]==colour)
	{
		if (colour=='o')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}
	}

	else if (g[1]=='w'&&o[3]==colour)
	{
		if (colour=='g')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}
	}

	else if (r[1]=='w'&&g[3]==colour)//UNTESTED, ERROR PRONE
	{
		if (colour=='r')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}
	}

	else if (y[9]=='w'&&g[9]==colour)//yellow face white side up
	{
		if (colour=='r')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}
	}//brw

	else if (y[3]=='w'&&o[9]==colour)
	{
		if (colour=='g')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}
	}

	else if (y[1]=='w'&&b[9]==colour)
	{
		if (colour=='o')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}
	}

	else if (y[7]=='w'&&r[9]==colour)
	{
		if (colour=='b')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}
	}

	else if (r[7]=='w'&&y[9]==colour)//yellow face bottom left white
	{
		if (colour=='r')
		{
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
		}
	}//brw

	else if (g[7]=='w'&&y[3]==colour)
	{
		if (colour=='g')
		{
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
		}
	}

	else if (o[7]=='w'&&y[1]==colour)
	{
		if (colour=='o')
		{
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 0);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
		}
	}

	else if (b[7]=='w'&&y[7]==colour)
	{
		if (colour=='b')
		{
			rotate('b', 0);
			rotate('y', 0);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 0);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 0);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
		}
	}

	else if (r[9]=='w'&&b[7]==colour)//yellow face bottom right white
	{
		if (colour=='b')
		{
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}
	}

	else if (b[9]=='w'&&o[7]==colour)
	{
		if (colour=='o')
		{
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}
	}

	else if (o[9]=='w'&&g[7]==colour)
	{
		if (colour=='g')
		{
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (colour=='r')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}
	}

	else if (g[9]=='w'&&r[7]==colour)
	{
		if (colour=='r')
		{
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (colour=='b')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (colour=='o')
		{
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (colour=='g')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}
	}
}

void orientColouredEdge(char colour)//right side colour with white facing up
{
	if (colour=='r')//red green piece
	{
		if (r[8]=='r'&&y[8]=='g')//easiest config
		{
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (g[8]=='r'&&y[6]=='g')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (o[8]=='r'&&y[2]=='g')
		{
			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (b[8]=='r'&&y[4]=='g')
		{
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (r[8]=='g'&&y[8]=='r')//above but flipped
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
		}

		else if (g[8]=='g'&&y[6]=='r')
		{
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
		}

		else if (o[8]=='g'&&y[2]=='r')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
		}

		else if (b[8]=='g'&&y[4]=='r')
		{
			rotate('y', 1);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
		}

		else if (r[4]=='r'&&g[6]=='g')//middle, colour on left side
		{}

		else if (g[4]=='r'&&o[6]=='g')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);

			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (o[4]=='r'&&b[6]=='g')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);

			rotate('y', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (b[4]=='r'&&r[6]=='g')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);

			rotate('y', 0);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (r[4]=='g'&&g[6]=='r')//above but flipped
		{
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);

			rotate('y', 0);

			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
		}

		else if (g[4]=='g'&&o[6]=='r')//good
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);

			rotate('y', 1);
			rotate('y', 1);

			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
		}

		else if (o[4]=='g'&&b[6]=='r')//good
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);

			rotate('y', 0);

			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
		}

		else if (b[4]=='g'&&r[6]=='r')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);

			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);
		}
	}

	else if (colour=='g')//green orange piece
	{
		if (g[8]=='g'&&y[6]=='o')//easiest config
		{
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (o[8]=='g'&&y[2]=='o')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (b[8]=='g'&&y[4]=='o')
		{
			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (r[8]=='g'&&y[8]=='o')
		{
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (g[8]=='o'&&y[6]=='g')//above but flipped
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
		}

		else if (o[8]=='o'&&y[2]=='g')
		{
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
		}

		else if (b[8]=='o'&&y[4]=='g')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
		}

		else if (r[8]=='o'&&y[8]=='g')
		{
			rotate('y', 1);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
		}

		else if (g[4]=='g'&&o[6]=='o')//middle, colour on left side
		{}

		else if (o[4]=='g'&&b[6]=='o')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);

			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (b[4]=='g'&&r[6]=='o')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);

			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (r[4]=='g'&&g[6]=='o')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);

			rotate('y', 0);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (g[4]=='o'&&o[6]=='g')//above but flipped
		{
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);

			rotate('y', 0);

			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 0);
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
		}

		else if (o[4]=='o'&&b[6]=='g')//good
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);

			rotate('y', 1);
			rotate('y', 1);

			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
		}

		else if (b[4]=='o'&&r[6]=='g')//good
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);

			rotate('y', 0);

			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
		}

		else if (r[4]=='o'&&g[6]=='g')//good
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);

			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);
		}
	}

	else if (colour=='o')//orange blue piece
	{
		if (o[8]=='o'&&y[2]=='b')//easiest config
		{
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (b[8]=='o'&&y[4]=='b')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (r[8]=='o'&&y[8]=='b')
		{
			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (g[8]=='o'&&y[6]=='b')
		{
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (o[8]=='b'&&y[2]=='o')//above but flipped
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
		}

		else if (b[8]=='b'&&y[4]=='o')
		{
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
		}

		else if (r[8]=='b'&&y[8]=='o')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
		}

		else if (g[8]=='b'&&y[6]=='o')
		{
			rotate('y', 1);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
		}

		else if (o[4]=='o'&&b[6]=='b')//middle, colour on left side
		{}

		else if (b[4]=='o'&&r[6]=='b')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);

			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (r[4]=='o'&&g[6]=='b')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);

			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (g[4]=='o'&&o[6]=='b')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);

			rotate('y', 0);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (o[4]=='b'&&b[6]=='o')//above but flipped
		{
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);

			rotate('y', 0);

			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 0);
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
		}

		else if (b[4]=='b'&&r[6]=='o')//good
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);

			rotate('y', 1);
			rotate('y', 1);

			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
		}

		else if (r[4]=='b'&&g[6]=='o')//good
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);

			rotate('y', 0);

			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
		}

		else if (g[4]=='b'&&o[6]=='o')//good
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);

			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);
		}
	}

	else if (colour=='b')//orange blue piece
	{
		if (b[8]=='b'&&y[4]=='r')//easiest config
		{
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (r[8]=='b'&&y[8]=='r')
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (g[8]=='b'&&y[6]=='r')
		{
			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (o[8]=='b'&&y[2]=='r')
		{
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (b[8]=='r'&&y[4]=='b')//above but flipped
		{
			rotate('y', 1);
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
		}

		else if (r[8]=='r'&&y[8]=='b')
		{
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
		}

		else if (g[8]=='r'&&y[6]=='b')
		{
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
		}

		else if (o[8]=='r'&&y[2]=='b')
		{
			rotate('y', 1);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
		}

		else if (b[4]=='b'&&r[6]=='r')//middle, colour on left side
		{}

		else if (r[4]=='b'&&g[6]=='r')
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);

			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (g[4]=='b'&&o[6]=='r')
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);

			rotate('y', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (o[4]=='b'&&b[6]=='r')
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);

			rotate('y', 0);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (b[4]=='r'&&r[6]=='b')//above but flipped
		{
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);

			rotate('y', 0);

			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
			rotate('y', 0);
			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
		}

		else if (r[4]=='r'&&g[6]=='b')//good
		{
			rotate('r', 0);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 0);
			rotate('g', 0);

			rotate('y', 1);
			rotate('y', 1);

			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
		}

		else if (g[4]=='r'&&o[6]=='b')//good
		{
			rotate('g', 0);
			rotate('y', 1);
			rotate('g', 1);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 0);
			rotate('o', 0);

			rotate('y', 0);

			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
		}

		else if (o[4]=='r'&&b[6]=='b')//good
		{
			rotate('o', 0);
			rotate('y', 1);
			rotate('o', 1);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 0);
			rotate('b', 0);

			rotate('b', 0);
			rotate('y', 1);
			rotate('b', 1);
			rotate('y', 1);
			rotate('r', 1);
			rotate('y', 0);
			rotate('r', 0);
		}
	}
}

void orientYellowCross()
{
	if (y[2]=='y'&&y[4]=='y'&&y[6]=='y'&&y[8]=='y')//cross
	{}

	else if (y[4]=='y'&&y[6]=='y')//straight line
	{
		rotate('r', 1);
		rotate('g', 1);
		rotate('y', 1);
		rotate('g', 0);
		rotate('y', 0);
		rotate('r', 0);
	}

	else if (y[2]=='y'&&y[8]=='y')
	{
		rotate('y', 1);

		rotate('r', 1);
		rotate('g', 1);
		rotate('y', 1);
		rotate('g', 0);
		rotate('y', 0);
		rotate('r', 0);
	}

	else if (y[2]=='y'&&y[4]=='y')//L shape
	{
		rotate('r', 1);
		rotate('y', 1);
		rotate('g', 1);
		rotate('y', 0);
		rotate('g', 0);
		rotate('r', 0);
	}

	else if (y[2]=='y'&&y[6]=='y')
	{
		rotate('y', 0);

		rotate('r', 1);
		rotate('y', 1);
		rotate('g', 1);
		rotate('y', 0);
		rotate('g', 0);
		rotate('r', 0);
	}

	else if (y[6]=='y'&&y[8]=='y')
	{
		rotate('y', 1);
		rotate('y', 1);

		rotate('r', 1);
		rotate('y', 1);
		rotate('g', 1);
		rotate('y', 0);
		rotate('g', 0);
		rotate('r', 0);
	}

	else if (y[4]=='y'&&y[8]=='y')
	{
		rotate('y', 1);

		rotate('r', 1);
		rotate('y', 1);
		rotate('g', 1);
		rotate('y', 0);
		rotate('g', 0);
		rotate('r', 0);
	}

	else
	{
		rotate('r', 1);
		rotate('y', 1);
		rotate('g', 1);
		rotate('y', 0);
		rotate('g', 0);
		rotate('r', 0);

		rotate('y', 1);

		rotate('r', 1);
		rotate('g', 1);
		rotate('y', 1);
		rotate('g', 0);
		rotate('y', 0);
		rotate('r', 0);
	}
}

void orientYellowFace()
{
	while (!(y[1]=='y'&&y[3]=='y'&&y[7]=='y'&&y[9]=='y'))//while all corners aren't solved
	{
		while (y[9]=='y')
			rotate('y', 1);

		while (y[9]!='y')
		{
			rotate('g', 0);
			rotate('w', 0);
			rotate('g', 1);
			rotate('w', 1);
		}
	}
}

void permuteYellowCorners()
{
	if (!(r[7]==r[9]||g[7]==g[9]||o[7]==o[9]||b[7]==b[9]))
	{
		rotate('g', 1);
		rotate('y', 1);
		rotate('g', 0);
		rotate('y', 0);
		rotate('g', 0);
		rotate('r', 1);
		rotate('g', 1);
		rotate('g', 1);
		rotate('y', 0);
		rotate('g', 0);
		rotate('y', 0);
		rotate('g', 1);
		rotate('y', 1);
		rotate('g', 0);
		rotate('r', 0);
	}

	while (b[7]!=b[9])
		rotate('y', 1);

	if (!(r[7]==r[9]&&g[7]==g[9]&&o[7]==o[9]&&b[7]==b[9]))
	{
		rotate('g', 1);
		rotate('y', 1);
		rotate('g', 0);
		rotate('y', 0);
		rotate('g', 0);
		rotate('r', 1);
		rotate('g', 1);
		rotate('g', 1);
		rotate('y', 0);
		rotate('g', 0);
		rotate('y', 0);
		rotate('g', 1);
		rotate('y', 1);
		rotate('g', 0);
		rotate('r', 0);
	}

	while(r[7]!='r')
		rotate('y', 1);
}

void permuteYellowEdges()
{
	if (r[8]=='o'&&o[8]=='r'&&g[8]=='b'&&b[8]=='g')//H perm
	{
		rotate('r', 1);
		rotate('r', 1);
		rotate('o', 1);
		rotate('o', 1);

		rotate('w', 1);

		rotate('r', 1);
		rotate('r', 1);
		rotate('o', 1);
		rotate('o', 1);

		rotate('w', 1);
		rotate('w', 1);

		rotate('r', 1);
		rotate('r', 1);
		rotate('o', 1);
		rotate('o', 1);

		rotate('w', 1);

		rotate('r', 1);
		rotate('r', 1);
		rotate('o', 1);
		rotate('o', 1);

		rotate('w', 1);
		rotate('w', 1);
		rotate('y', 1);
		rotate('y', 1);
	}

	else if (r[8]=='g'&&g[8]=='r'&&o[8]=='b'&&b[8]=='o')//Z perm
	{
		rotate('b', 1);
		rotate('b', 1);
		rotate('g', 1);
		rotate('g', 1);

		rotate('w', 1);

		rotate('b', 1);
		rotate('b', 1);
		rotate('g', 1);
		rotate('g', 1);

		rotate('y', 1);

		rotate('b', 1);
		rotate('g', 0);

		rotate('r', 1);
		rotate('r', 1);

		rotate('b', 1);
		rotate('b', 1);
		rotate('g', 1);
		rotate('g', 1);

		rotate('o', 1);
		rotate('o', 1);

		rotate('b', 1);
		rotate('g', 0);

		rotate('y', 1);
		rotate('y', 1);
	}

	else if (r[8]=='b'&&b[8]=='r'&&o[8]=='g'&&g[8]=='o')//Z perm
	{
		rotate('r', 1);
		rotate('r', 1);
		rotate('o', 1);
		rotate('o', 1);

		rotate('w', 1);

		rotate('r', 1);
		rotate('r', 1);
		rotate('o', 1);
		rotate('o', 1);

		rotate('y', 1);

		rotate('r', 1);
		rotate('o', 0);

		rotate('b', 1);
		rotate('b', 1);

		rotate('r', 1);
		rotate('r', 1);
		rotate('o', 1);
		rotate('o', 1);

		rotate('g', 1);
		rotate('g', 1);

		rotate('r', 1);
		rotate('o', 0);

		rotate('y', 1);
		rotate('y', 1);
	}

	while(!(o[7]==o[8]&&o[8]==o[9]))
		rotate('y', 1);

	if (g[9]==b[8])//normal 3 cycle
	{
		rotate('r', 1);
		rotate('r', 1);
		rotate('y', 1);

		rotate('b', 1);
		rotate('g', 0);

		rotate('r', 1);
		rotate('r', 1);

		rotate('b', 0);
		rotate('g', 1);

		rotate('y', 1);
		rotate('r', 1);
		rotate('r', 1);
	}

	else if (b[7]==g[8])
	{
		rotate('r', 1);
		rotate('r', 1);
		rotate('y', 0);

		rotate('b', 1);
		rotate('g', 0);

		rotate('r', 1);
		rotate('r', 1);

		rotate('b', 0);
		rotate('g', 1);

		rotate('y', 0);
		rotate('r', 1);
		rotate('r', 1);
	}

	while (r[8]!='r')
		rotate('y', 1);
}

void rotateArray(char face, bool direction)//ONLY FOR PRESCRAMBLE TESTING, DELETE AFTER
{
	if (face=='w')
	{
		if (direction)
		{
			swap(r[1], b[1]);
			swap(r[2], b[2]);
			swap(r[3], b[3]);

			swap(o[1], b[1]);
			swap(o[2], b[2]);
			swap(o[3], b[3]);

			swap(o[1], g[1]);
			swap(o[2], g[2]);
			swap(o[3], g[3]);

			swap(w[1], w[7]);
			swap(w[7], w[9]);
			swap(w[9], w[3]);

			swap(w[2], w[4]);
			swap(w[4], w[8]);
			swap(w[8], w[6]);
		}

		else
		{
			swap(r[1], g[1]);
			swap(r[2], g[2]);
			swap(r[3], g[3]);

			swap(o[1], g[1]);
			swap(o[2], g[2]);
			swap(o[3], g[3]);

			swap(o[1], b[1]);
			swap(o[2], b[2]);
			swap(o[3], b[3]);

			swap(w[1], w[3]);
			swap(w[3], w[9]);
			swap(w[9], w[7]);

			swap(w[2], w[6]);
			swap(w[6], w[8]);
			swap(w[8], w[4]);
		}
	}

	else if (face=='r')
	{
		if (direction)
		{
			swap(y[7], b[1]);
			swap(y[8], b[4]);
			swap(y[9], b[7]);

			swap(w[7], b[1]);
			swap(w[8], b[4]);
			swap(w[9], b[7]);

			swap(w[7], g[9]);
			swap(w[8], g[6]);
			swap(w[9], g[3]);

			swap(r[1], r[7]);
			swap(r[7], r[9]);
			swap(r[9], r[3]);

			swap(r[2], r[4]);
			swap(r[4], r[8]);
			swap(r[8], r[6]);

		}

		else
		{
			swap(y[7], g[9]);
			swap(y[8], g[6]);
			swap(y[9], g[3]);

			swap(w[7], g[9]);
			swap(w[8], g[6]);
			swap(w[9], g[3]);

			swap(w[7], b[1]);
			swap(w[8], b[4]);
			swap(w[9], b[7]);

			swap(r[1], r[3]);
			swap(r[3], r[9]);
			swap(r[9], r[7]);

			swap(r[2], r[6]);
			swap(r[6], r[8]);
			swap(r[8], r[4]);
		}
	}

	else if (face=='b')
	{
		if (direction)
		{
			swap(y[1], o[1]);
			swap(y[4], o[4]);
			swap(y[7], o[7]);

			swap(o[1], w[9]);
			swap(o[4], w[6]);
			swap(o[7], w[3]);

			swap(w[3], r[3]);
			swap(w[6], r[6]);
			swap(w[9], r[9]);

			swap(b[1], b[7]);
			swap(b[7], b[9]);
			swap(b[9], b[3]);

			swap(b[2], b[4]);
			swap(b[4], b[8]);
			swap(b[8], b[6]);
		}

		else
		{
			swap(y[1], r[9]);
			swap(y[4], r[6]);
			swap(y[7], r[3]);

			swap(w[3], r[3]);
			swap(w[6], r[6]);
			swap(w[9], r[9]);

			swap(w[3], o[7]);
			swap(w[6], o[4]);
			swap(w[9], o[1]);

			swap(b[1], b[3]);
			swap(b[3], b[9]);
			swap(b[9], b[7]);

			swap(b[2], b[6]);
			swap(b[6], b[8]);
			swap(b[8], b[4]);
		}
	}

	else if (face=='o')
	{
		if (direction)
		{
			swap(g[1], y[3]);
			swap(g[4], y[2]);
			swap(g[7], y[1]);

			swap(g[1], w[3]);
			swap(g[4], w[2]);
			swap(g[7], w[1]);

			swap(w[1], b[3]);
			swap(w[2], b[6]);
			swap(w[3], b[9]);

			swap(o[1], o[7]);
			swap(o[7], o[9]);
			swap(o[9], o[3]);

			swap(o[2], o[4]);
			swap(o[4], o[8]);
			swap(o[8], o[6]);
		}

		else
		{
			swap(y[1], b[3]);
			swap(y[2], b[6]);
			swap(y[3], b[9]);

			swap(w[1], b[3]);
			swap(w[2], b[6]);
			swap(w[3], b[9]);

			swap(w[1], g[7]);
			swap(w[2], g[4]);
			swap(w[3], g[1]);

			swap(o[1], o[3]);
			swap(o[3], o[9]);
			swap(o[9], o[7]);

			swap(o[2], o[6]);
			swap(o[6], o[8]);
			swap(o[8], o[4]);
		}
	}

	else if (face=='g')
	{
		if (direction)
		{
			swap(r[1], y[9]);
			swap(r[4], y[6]);
			swap(r[7], y[3]);

			swap(r[1], w[1]);
			swap(r[4], w[4]);
			swap(r[7], w[7]);

			swap(w[1], o[9]);
			swap(w[4], o[6]);
			swap(w[7], o[3]);

			swap(g[1], g[7]);
			swap(g[7], g[9]);
			swap(g[9], g[3]);

			swap(g[2], g[4]);
			swap(g[4], g[8]);
			swap(g[8], g[6]);
		}

		else
		{
			swap(y[3], o[3]);
			swap(y[6], o[6]);
			swap(y[9], o[9]);

			swap(w[1], o[9]);
			swap(w[4], o[6]);
			swap(w[7], o[3]);

			swap(w[1], r[1]);
			swap(w[4], r[4]);
			swap(w[7], r[7]);

			swap(g[1], g[3]);
			swap(g[3], g[9]);
			swap(g[9], g[7]);

			swap(g[2], g[6]);
			swap(g[6], g[8]);
			swap(g[8], g[4]);
		}
	}

	else if (face=='y')
	{
		if (direction)
		{
			swap(r[7], g[7]);
			swap(r[8], g[8]);
			swap(r[9], g[9]);

			swap(o[7], g[7]);
			swap(o[8], g[8]);
			swap(o[9], g[9]);

			swap(o[7], b[7]);
			swap(o[8], b[8]);
			swap(o[9], b[9]);

			swap(y[1], y[7]);
			swap(y[7], y[9]);
			swap(y[9], y[3]);

			swap(y[2], y[4]);
			swap(y[4], y[8]);
			swap(y[8], y[6]);
		}

		else
		{
			swap(r[7], b[7]);
			swap(r[8], b[8]);
			swap(r[9], b[9]);

			swap(o[7], b[7]);
			swap(o[8], b[8]);
			swap(o[9], b[9]);

			swap(o[7], g[7]);
			swap(o[8], g[8]);
			swap(o[9], g[9]);

			swap(y[1], y[3]);
			swap(y[3], y[9]);
			swap(y[9], y[7]);

			swap(y[2], y[6]);
			swap(y[6], y[8]);
			swap(y[8], y[4]);
		}
	}
}

char convertButtonsToChar()
{
	while(!getButtonPress(buttonAny)&&!SensorValue[S4])
	{}

	if (getButtonPress(buttonEnter))
		return 'w';

	else if (getButtonPress(buttonDown))
		return 'r';

	else if (getButtonPress(buttonRight))
		return 'b';

	else if (getButtonPress(buttonUp))
		return 'o';

	else if (getButtonPress(buttonLeft))
		return 'g';

	else
	{
		return 'y';
		wait1Msec(100);
	}
}

void userInputColour()
{
	displayString(0, "Archie, automatic Rubik's Cube Solver");

	displayString(2, "Input colours on white face ");
	displayString(3, "according to the diagram ");
	for (int index=1; index<=9; index++)
	{
		w[index]=convertButtonsToChar();
		while(getButtonPress(buttonAny)||SensorValue[S4])
		{}
		displayString(4+index, "%c", w[index]);
	}
	eraseDisplay();
	displayString(0, "Archie, automatic Rubik's Cube Solver");

	displayString(2, "Input colours on red face ");
	displayString(3, "according to the diagram ");
	for (int index=1; index<=9; index++)
	{
		r[index]=convertButtonsToChar();
		while(getButtonPress(buttonAny)||SensorValue[S4])
		{}
		displayString(4+index, "%c", r[index]);
	}
	eraseDisplay();
	displayString(0, "Archie, automatic Rubik's Cube Solver");

	displayString(2, "Input colours on blue face ");
	displayString(3, "according to the diagram ");
	for (int index=1; index<=9; index++)
	{
		b[index]=convertButtonsToChar();
		while(getButtonPress(buttonAny)||SensorValue[S4])
		{}
		displayString(4+index, "%c", b[index]);
	}
	eraseDisplay();
	displayString(0, "Archie, automatic Rubik's Cube Solver");

	displayString(2, "Input colours on orange face ");
	displayString(3, "according to the diagram ");
	for (int index=1; index<=9; index++)
	{
		o[index]=convertButtonsToChar();
		while(getButtonPress(buttonAny)||SensorValue[S4])
		{}
		displayString(4+index, "%c", o[index]);
	}
	eraseDisplay();
	displayString(0, "Archie, automatic Rubik's Cube Solver");

	displayString(2, "Input colours on green face ");
	displayString(3, "according to the diagram ");
	for (int index=1; index<=9; index++)
	{
		g[index]=convertButtonsToChar();
		while(getButtonPress(buttonAny)||SensorValue[S4])
		{}
		displayString(4+index, "%c", g[index]);
	}
	eraseDisplay();
	displayString(0, "Archie, automatic Rubik's Cube Solver");

	displayString(2, "Input colours on yellow face ");
	displayString(3, "according to the diagram ");
	for (int index=1; index<=9; index++)
	{
		y[index]=convertButtonsToChar();
		while(getButtonPress(buttonAny)||SensorValue[S4])
		{}
		displayString(4+index, "%c", y[index]);
	}
	eraseDisplay();
	displayString(0, "Archie, automatic Rubik's Cube Solver");


	displayString(2, "Colour input complete, press ");
	displayString(3, "enter to commence solve");
	wait1Msec(2000);
}

task main()
{
	displayString(0, "Archie, automatic Rubik's Cube Solver");

	SensorValue[S4]=sensorEV3_Touch;

	userInputColour();

	eraseDisplay();

	displayString(1, "White face values:");
	displayString(2, "%c %c %c %c %c %c %c %c %c", w[1], w[2], w[3], w[4], w[5], w[6], w[7], w[8], w[9]);

	displayString(3, "Red face values:");
	displayString(4, "%c %c %c %c %c %c %c %c %c", r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8], r[9]);

	displayString(5, "Blue face values:");
	displayString(6, "%c %c %c %c %c %c %c %c %c", b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9]);

	displayString(7, "Orange face values:");
	displayString(8, "%c %c %c %c %c %c %c %c %c", o[1], o[2], o[3], o[4], o[5], o[6], o[7], o[8], o[9]);

	displayString(9, "Green face values:");
	displayString(10, "%c %c %c %c %c %c %c %c %c", g[1], g[2], g[3], g[4], g[5], g[6], g[7], g[8], g[9]);

	displayString(11, "Yellow face values:");
	displayString(12, "%c %c %c %c %c %c %c %c %c", y[1], y[2], y[3], y[4], y[5], y[6], y[7], y[8], y[9]);

	while(!getButtonPress(buttonEnter))
	{}

	while(getButtonPress(buttonEnter))
	{}

	bool timeLimit = true;

	time1[T1] = 0;

	orientWhiteEdge('r');

	if (time1(T1) <= 2100000)
	{
		orientWhiteEdge('b');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientWhiteEdge('o');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientWhiteEdge('g');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientWhiteCorner('r');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientWhiteCorner('b');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientWhiteCorner('o');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientWhiteCorner('g');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientColouredEdge('r');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientColouredEdge('g');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientColouredEdge('o');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientColouredEdge('b');
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientYellowCross();
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		orientYellowFace();
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		permuteYellowCorners();
		timeLimit = false;
	}

	if (time1(T1) <= 2100000)
	{
		permuteYellowEdges();
		timeLimit = false;
	}

	if (!timeLimit)
		displayString(7, "Error: exceeded time limit of 35 minutes.");

	else if (SensorValue[S4])
		displayString(7, "Error: abort button.");

	else
		displayString(7, "Test: Success REMOVE IN FINAL");

	wait1Msec(5000);
}
