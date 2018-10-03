#define _CRT_SECURE_NO_WARNINGS
# include "stdafx.h"
# include "iGraphics.h"
# include "stdlib.h"


#include<time.h>


int gamer_x = 0, gamer_y = 512, foe[4][2] = { 0 }, i, temp, j, bullet[150][3] = { 0 }, bullet_on = 0, score = 0, foe_bullet[4][5][5] = { 0 }, life = 3, gamer_state[3] = { 1, 0, 0 };
char str_score[25], str_life[3], convert_to_string[100], scorestr[12], str_level[3],settime = 0;
FILE* fp;
int menu = 0, load = 320, boss_bullet[100][3] = { 0 },level_start = 0, l = 1, load1 = 2, load2 = 325, load3 = 2, load4 = 331, load5 = 2, high_score = 0, initial1 = 660, initial2 = 0, level = 1, initial3 = 513, initial4 = 0, initial5 = 453, score1[5], again = 1, boss_off = 1, boss_x = 384, boss_y = 384, boss_pos = 0, boss_pos_temp = 0, boss_death = 0, life_on = 0, life_x, life_y;
char user_name[15];
int len = 0, gettingname = 0, file = 0, d = 0;
char *filename;
struct game{
	char name[10];
	int mv;
} leaderboard[11];

bool cmp(game a, game b)
{
	return a.mv > b.mv;
}
void input_name(){
	iSetColor(255, 255, 0);
	sprintf_s(str_score, "%d", score);
	iShowBMP(0, 0, "back-1.bmp");
	iText(310, 300, str_score, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(150, 350, "Your Name", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(150, 300, "Your Score : ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(290, 350, user_name, GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(255, 0, 255);
	iRectangle(280, 340, 120, 30);
}

void InputFromFile()
{
	FILE *f;
	if ((f = fopen("leaderboard.txt", "r")) == NULL)
	{

	}
	else
	{
		for (int i = 0; i<11; i++)
		{
			fscanf(f, "%s %d", leaderboard[i].name, &leaderboard[i].mv);
		}
	}
	fclose(f);
}


void WriteToFile()
{
	FILE *f;
	if ((f = fopen("leaderboard.txt", "w")) == NULL)
	{

	}
	else
	{
		for (int i = 0; i<11; i++)
		{
			fprintf(f, "%s %d\n", leaderboard[i].name, leaderboard[i].mv);

		}
	}
	fclose(f);
}

void showleaderboard(){
	iSetColor(255, 255, 0);
	iText(150, 500, "***LEADERBOARD***", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(100, 450, "Serial", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(200, 450, "Name", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(400, 450, "Score", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(400, 50, "BACK", GLUT_BITMAP_HELVETICA_18);
	iRectangle(390, 40, 80, 30);
	

	int h = 400;
	for (int i = 0; i < 10; i++, h -= 30)
	{
		char str[10];
		sprintf_s(str, "%d", i + 1);
		iText(100, h, str, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(200, h, leaderboard[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf_s(str, "%d", leaderboard[i].mv);
		iText(400, h, str, GLUT_BITMAP_TIMES_ROMAN_24);
		
	}
}

void boss_bullet_draw(int boss_x, int boss_y)
{

	for (j = 0; j<100; j++)
	{
		if (boss_bullet[j][2] == 0)
		{
			boss_bullet[j][0] = boss_x;
			boss_bullet[j][1] = boss_y;
			boss_bullet[j][2] = 1;
			break;

		}

	}


}



/*
	author: S. M. Shahriar Nirjon
	last modified: August 8, 2008
	function iDraw() is called again and again by the system.
*/





void life_draw()
{
	while (1)
	{
		temp = rand() % 800;
		if (temp>512)
		{
			life_x = temp;
			break;
		}
	}

	while (1)
	{
		temp = rand() % 440;
		for (j = 0; j<4; j++)
		{

			if (temp + 64 >= foe[j][1] && temp <= foe[j][1] + 64)
				break;
		}
		if (j == 4)
		{
			life_y = temp;
			break;
		}
	}


}
void boss_draw()
{
	 boss_off = 0;
	//iResumeTimer(60000);
}
void foe_draw()
{

	while (1)
	{
		temp = rand() % 800;
		if (temp>512)
		{
			foe[i][0] = temp;
			break;
		}
	}

	while (1)
	{
		temp = rand() % 440;
		for (j = 0; j<4; j++)
		{
			if (j == i) continue;
			if (temp<foe[j][1] + 100 && temp>foe[j][1] - 100)
				break;
		}
		if (j == 4)
		{
			foe[i][1] = temp;
			break;
		}
	}
}




void bullet_draw(int bullet_x, int bullet_y)
{

	for (i = 0; i<512; i++)
	{
		if (bullet[i][2] == 0)
		{
			bullet[i][0] = bullet_x;
			bullet[i][1] = bullet_y;
			bullet[i][2] = 1;
			break;

		}

	}


}



void iDraw()
{
	iClear();
	if (file == 0) InputFromFile(), file = 1;
	else WriteToFile();

	if (menu == 0){
		iShowBMP(0, 0, "menu-1-plane.bmp");
		iSetColor(255, 255, 0);
		iText(325, 80, "LOADING...", GLUT_BITMAP_HELVETICA_18);

		iSetColor(255, 0, 0);
		iRectangle(320, 60, 100, 10);
		iSetColor(255, 255, 0);
		iFilledRectangle(load, 60, 2, 10);
		l++;
		if (l % 5 == 0){
			iFilledRectangle(320, 60, load1, 10);
			load++;
			load1++;
		}

		if (load == 419)menu = 1;


	}

	else if (menu == 1){
			{if (again == 1)
				iShowBMP(0, 0, "menu new-1.bmp");
			iShowBMP(0, initial1, "menu new-2.bmp");
			iShowBMP(initial3, initial5, "menu new-3.bmp");
			if (initial1 >= 551 && initial2 == 0){

				initial1--;
				if (initial1 == 550)initial2 = 2;
			}
			if (initial2 == 2 && initial1 <= 593){
				initial1++;
				{
					if (initial1 == 592)initial2 = 1;
				}
			}
			if (initial2 == 1){

				if (initial3 >= 3){
					initial3 = initial3 - 4;
					if (initial3 == 5)initial4 = 1;

				}
			}
			if (initial4 == 1 && initial5 <= 528){

				initial5++;
			}
			}

		if (again == 0){
			iShowBMP(0, 0, "menu new-1.bmp");
			iShowBMP(0, 592, "menu new-2.bmp");
			iShowBMP(5, 528, "menu new-3.bmp");
		}

		iShowBMP(20, 370, "new game.bmp");
		iShowBMP(400, 370, "help.bmp");
		iShowBMP(310, 220, "high score.bmp");
		iShowBMP(50, 220, "credits.bmp");
		iShowBMP(210, 70, "exit.bmp");
	}
	else if (menu == 3){
		iSetColor(255, 255, 0);
		showleaderboard();

	}
	else if (menu == 4){
		iShowBMP(0, 0, "hepl-1.bmp");
		iShowBMP(260, 407, "plane-11.bmp");
		iShowBMP(390, 438, "life.bmp");
		iSetColor(255, 255, 0);
		iText(400, 50, "BACK", GLUT_BITMAP_HELVETICA_18);
		iRectangle(390, 40, 80, 30);
	}
	else if (menu == 5){
		iSetColor(255, 255, 0);
		iText(300, 450, "CREDITS", GLUT_BITMAP_HELVETICA_18);
		iRectangle(290, 440, 100, 40);
		iText(30, 400, "This game is developed by : ", GLUT_BITMAP_HELVETICA_18);
		iText(30, 378, "Trishna Chakrabarty &", GLUT_BITMAP_HELVETICA_18);
		iText(30, 356, "Aminul Islam Sojal", GLUT_BITMAP_HELVETICA_18);
		iText(30, 334, "Under the supervision of Tanveer Ahmed Khan,", GLUT_BITMAP_HELVETICA_18);
		iText(30, 312, "Lecturer,Department of CSE,BUET", GLUT_BITMAP_HELVETICA_18);
		iText(30, 268, "Contact with us :", GLUT_BITMAP_HELVETICA_18);
		iText(150, 246, "Email : tinkertrish94@gmail.com ", GLUT_BITMAP_HELVETICA_18);
		iText(205, 224, "aminul7506@gmail.com", GLUT_BITMAP_HELVETICA_18);
		iText(150, 202, "Mobile : ", GLUT_BITMAP_HELVETICA_18);
		iText(210, 180, "01750903875", GLUT_BITMAP_HELVETICA_18);
		iText(210, 158, "01715461477", GLUT_BITMAP_HELVETICA_18);
		iText(30, 114, "copyright@2015.All rights reserved.", GLUT_BITMAP_HELVETICA_18);
		iText(400, 50, "BACK", GLUT_BITMAP_HELVETICA_18);
		iRectangle(390, 40, 80, 30);

	}
	if (menu == 6){
		iShowBMP(0, 0, "game over-2.BMP");

		if (d > 300){
			d = 0;
			menu = 7;
		}
		else
			d++;



	}
	else if (menu == 7){
		gettingname = 1;
		input_name();
	}


	//main game starts here//

	else if (menu == 2 && level == 1){


		iShowBMP(0, 0, "sky-3.BMP");

		if (gamer_state[0] == 1) iShowBMP(gamer_x, gamer_y, "plane-11.BMP");
		else if (gamer_state[1] == 1) iShowBMP(gamer_x, gamer_y, "plane-1_left.BMP");
		else if (gamer_state[2] == 1) iShowBMP(gamer_x, gamer_y, "plane-1_right.BMP");
		


		int ignoreColor = 0 + (1 << 8) * 255 + (1 << 16) * 0;
		if (boss_off)
		{
			for (i = 0; i < 4; i++)
			{
				if (foe[i][0] <= 0)
					foe_draw();

				foe[i][0]-=2;
				if (foe[i][0]<gamer_x + 58 && foe[i][0]>gamer_x - 64 && foe[i][1]<gamer_y + 64 && foe[i][1]>gamer_y - 64)
				{
					life--;
					iDelay(1);

					gamer_x = 0;
					gamer_y = 512;

				}


				if (foe[i][0] < 512 && foe[i][0]>0 && foe[i][0] % 200 == 0)
				{
					for (j = 0; j < 5; j++)
					{
						if (foe_bullet[i][j][2] == 0)
						{
							foe_bullet[i][j][2] = 1;
							foe_bullet[i][j][0] = foe[i][0];
							foe_bullet[i][j][1] = foe[i][1] + 32;
							break;

						}
					}
				}
			}
		}





		if (!boss_off)
		{
			iShowBMP(boss_x, boss_y, "boss.BMP");
			if (boss_pos_temp % 20 == 0) boss_pos = rand() % 4;
			if (boss_pos == 0)
			{
				boss_x++;
				if (boss_x > 384)
					boss_x = 384;
			}
			if (boss_pos == 1)
			{
				boss_x--;
				if (boss_x < 0)
					boss_x = 0;
			}
			if (boss_pos == 2)
			{
				boss_y += 5;
				if (boss_y > 384)
					boss_y = 384;
			}
			if (boss_pos == 3)
			{
				boss_y -= 5;
				if (boss_y < 0)
					boss_y = 0;
			}
			boss_pos_temp++;
			if (boss_x % 20 == 0)
			{
				boss_bullet_draw(boss_x, boss_y + 64);
			}

		}
		if (boss_x <= gamer_x && boss_x + 128 >= gamer_x  && boss_y <= gamer_y  && boss_y + 128 >= gamer_y  &&  !(boss_off))
		{
			life--;
			iDelay(1);

			gamer_x = 0;
			gamer_y = 512;
		}
		if (boss_x <= gamer_x && boss_x + 128 >= gamer_x  && boss_y <= gamer_y  && boss_y + 128 >= gamer_y)
		{
			life--;
			iDelay(1);

			gamer_x = 0;
			gamer_y = 512;

		}
		if (boss_off)
		{
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (foe_bullet[i][j][2] == 1)
					{
						iSetColor(255, 255, 0);
						if (boss_off) iFilledCircle(foe_bullet[i][j][0], foe_bullet[i][j][1], 2, 10);
						foe_bullet[i][j][0] -= 3;
						if (foe_bullet[i][j][0] == gamer_x + 64 && foe_bullet[i][j][1] > gamer_y && foe_bullet[i][j][1] < gamer_y + 64)
						{
							life--;
							iDelay(1);
							gamer_x = 0;
							gamer_y = 512;

						}
					}




					if (foe_bullet[i][j][0] <= 0)
						foe_bullet[i][j][2] = 0;
				}
			}
		}

		if (bullet_on == 1)
		{
			bullet_on = 0;

			if (gamer_state[0] == 1) bullet_draw(gamer_x + 64, gamer_y + 32);
			else if (gamer_state[1] == 1 && gamer_y <= 480) bullet_draw(gamer_x + 64, gamer_y);
			else if (gamer_state[2] == 1 && gamer_y <= 480) bullet_draw(gamer_x + 64, gamer_y + 64);
		}
		for (i = 0; i < 150; i++)
		{
			if (bullet[i][2] == 1)
			{
				iSetColor(255, 255, 0);
				iFilledCircle(bullet[i][0], bullet[i][1], 2, 100);
				if (gamer_state[0] == 1) bullet[i][0] += 5;
				else if (gamer_state[1] == 1)
				{
					bullet[i][0] += 5;
					bullet[i][1] = gamer_x - bullet[i][0] + gamer_y + 64;
				}
				else if (gamer_state[2] == 1)
				{
					bullet[i][0] += 5;
					bullet[i][1] = bullet[i][0] - gamer_x + gamer_y;
				}
				if (boss_off)
				{
					for (j = 0; j < 4; j++)
					{
						if ((bullet[i][0] <= foe[j][0] + 64) && (bullet[i][0] >= foe[j][0]) && (bullet[i][1] <= foe[j][1] + 64) && (bullet[i][1] >= foe[j][1]))
						{
							foe[j][0] = -10;
							score += 5;
						}


					}
				}
				if ((bullet[i][0] <= boss_x + 128) && (bullet[i][0] >= boss_x) && (bullet[i][1] <= boss_y + 128) && (bullet[i][1] >= boss_y) && !(boss_off))
				{
					boss_death++;
					bullet[i][2] = 0;
					score += 5;
					if (boss_death == 10)
					{
						boss_off = 1;
						boss_death = 0;
						level_start = 1;

						//menu = 6;

					}
				}
				if (bullet[i][0] > 512)
					bullet[i][2] = 0;
			}
		}
		if (boss_off)
		{
			iShowBMP(foe[0][0], foe[0][1], "plane-2.BMP");
			iShowBMP(foe[1][0], foe[1][1], "plane-3.BMP");
			iShowBMP(foe[2][0], foe[2][1], "plane-4.BMP");
			iShowBMP(foe[3][0], foe[3][1], "plane-5.BMP");
		}
		iSetColor(0, 0, 256);


		sprintf_s(str_score, "%d", score);
		iText(74, 597, str_score, GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf_s(str_life, "%d", life);
		iText(229, 597, str_life, GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf_s(str_level, "%d", level);
		iText(440, 597, str_level, GLUT_BITMAP_TIMES_ROMAN_24);
		if (score % 100 == 0 && boss_off)
		{
			life_on = 1;
			life_draw();

		}
		if (life == 0) menu = 6;
		if (life_on == 1 && boss_off)
		{
			iShowBMP(life_x, life_y, "life.BMP");
			life_x -= 2;
			if (life_x <= 0)
				life_on = 0;

			if ((life_x <= gamer_x + 64) && (gamer_x <= life_x) && (life_y <= gamer_y + 64) && (gamer_y <= life_y))
			{
				life_x = -78;
				life_on = 0;
				life++;
			}
		}
		for (j = 0; j < 100; j++)
		{
			if (boss_bullet[j][2] == 1 && !(boss_off))
			{
				iSetColor(255, 255, 255);
				iFilledCircle(boss_bullet[j][0], boss_bullet[j][1], 5, 100);
				boss_bullet[j][0] -= 2;
				if (boss_bullet[j][0] <= 0) boss_bullet[j][2] = 0;
				if (boss_bullet[j][0] <= gamer_x + 64 && boss_bullet[j][0] >= gamer_x  && boss_bullet[j][1] > gamer_y && boss_bullet[j][1] < gamer_y + 64)
				{
					life--;
					boss_bullet[j][2] = 0;
					iDelay(1);
					gamer_x = 0;
					gamer_y = 512;

				}

			}
		}




		if (level_start == 1){
			level_start = 0;
			level = 2;
			menu = 8;

		}
	}
	else if (menu == 8 && level == 2){
		iShowBMP(0, 0, "back-1.bmp");
		iShowBMP(0, 0, "level-2.bmp");
		iFilledRectangle(load2, 186, 2, 12);
		l++;
		if (l % 4 == 0){
			iSetColor(0, 255, 255);
			iFilledRectangle(325, 186, load3, 12);
			load2++;
			load3++;
		}
		if (load2 == 450){
			menu = 9;
			gamer_x = 0;
			gamer_y = 512;
		}
	}
	else if (menu == 9 && level == 2){




		iShowBMP(0, 0, "sky-3.BMP");

		if (gamer_state[0] == 1) iShowBMP(gamer_x, gamer_y, "plane-11.BMP");
		else if (gamer_state[1] == 1) iShowBMP(gamer_x, gamer_y, "plane-1_left.BMP");
		else if (gamer_state[2] == 1) iShowBMP(gamer_x, gamer_y, "plane-1_right.BMP");

		int ignoreColor = 0 + (1 << 8) * 255 + (1 << 16) * 0;
		if (boss_off)
		{
			for (i = 0; i < 4; i++)
			{
				if (foe[i][0] <= 0)
					foe_draw();

				foe[i][0] -= 3;
				if (foe[i][0]<gamer_x + 58 && foe[i][0]>gamer_x - 64 && foe[i][1]<gamer_y + 64 && foe[i][1]>gamer_y - 64)
				{
					life--;
					iDelay(1);

					gamer_x = 0;
					gamer_y = 512;

				}


				if (foe[i][0] < 512 && foe[i][0]>0 && foe[i][0] % 200 == 0)
				{
					for (j = 0; j < 5; j++)
					{
						if (foe_bullet[i][j][2] == 0)
						{
							foe_bullet[i][j][2] = 1;
							foe_bullet[i][j][0] = foe[i][0];
							foe_bullet[i][j][1] = foe[i][1] + 32;
							break;

						}
					}
				}
			}
		}






		if (!boss_off)
		{
			iShowBMP(boss_x, boss_y, "boss.BMP");
			if (boss_pos_temp % 20 == 0) boss_pos = rand() % 4;
			if (boss_pos == 0)
			{
				boss_x++;
				if (boss_x > 384)
					boss_x = 384;
			}
			if (boss_pos == 1)
			{
				boss_x--;
				if (boss_x < 0)
					boss_x = 0;
			}
			if (boss_pos == 2)
			{
				boss_y += 5;
				if (boss_y > 384)
					boss_y = 384;
			}
			if (boss_pos == 3)
			{
				boss_y -= 5;
				if (boss_y < 0)
					boss_y = 0;
			}
			boss_pos_temp++;
			if (boss_x % 20 == 0)
			{
				boss_bullet_draw(boss_x, boss_y + 64);
			}

		}
		if (boss_x <= gamer_x && boss_x + 128 >= gamer_x  && boss_y <= gamer_y  && boss_y + 128 >= gamer_y  &&  !(boss_off))
		{
			life--;
			iDelay(1);

			gamer_x = 0;
			gamer_y = 512;
		}
		if (boss_x <= gamer_x && boss_x + 128 >= gamer_x  && boss_y <= gamer_y  && boss_y + 128 >= gamer_y)
		{
			life--;
			iDelay(1);

			gamer_x = 0;
			gamer_y = 512;


		}
		if (boss_x <= gamer_x && boss_x + 128 >= gamer_x  && boss_y <= gamer_y  && boss_y + 128 >= gamer_y)
		{
			life--;
			iDelay(1);

			gamer_x = 0;
			gamer_y = 512;

		}
		if (boss_off)
		{
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 10; j++)
				{
					if (foe_bullet[i][j][2] == 1)
					{
						iSetColor(255, 255, 0);
						if (boss_off) iFilledCircle(foe_bullet[i][j][0], foe_bullet[i][j][1], 2, 10);
						foe_bullet[i][j][0] -= 5;
						if (foe_bullet[i][j][0] == gamer_x + 64 && foe_bullet[i][j][1] > gamer_y && foe_bullet[i][j][1] < gamer_y + 64)
						{
							life--;
							iDelay(1);
							gamer_x = 0;
							gamer_y = 512;

						}
					}




					if (foe_bullet[i][j][0] <= 0)
						foe_bullet[i][j][2] = 0;
				}
			}
		}

		if (bullet_on == 1)
		{
			bullet_on = 0;

			if (gamer_state[0] == 1) bullet_draw(gamer_x + 64, gamer_y + 32);
			else if (gamer_state[1] == 1 && gamer_y <= 480) bullet_draw(gamer_x + 64, gamer_y);
			else if (gamer_state[2] == 1 && gamer_y <= 480) bullet_draw(gamer_x + 64, gamer_y + 64);
		}
		for (i = 0; i < 150; i++)
		{
			if (bullet[i][2] == 1)
			{
				iSetColor(255, 255, 0);
				iFilledCircle(bullet[i][0], bullet[i][1], 2, 100);
				if (gamer_state[0] == 1) bullet[i][0] += 5;
				else if (gamer_state[1] == 1)
				{
					bullet[i][0] += 5;
					bullet[i][1] = gamer_x - bullet[i][0] + gamer_y + 64;
				}
				else if (gamer_state[2] == 1)
				{
					bullet[i][0] += 5;
					bullet[i][1] = bullet[i][0] - gamer_x + gamer_y;
				}
				if (boss_off)
				{
					for (j = 0; j < 4; j++)
					{
						if ((bullet[i][0] <= foe[j][0] + 64) && (bullet[i][0] >= foe[j][0]) && (bullet[i][1] <= foe[j][1] + 64) && (bullet[i][1] >= foe[j][1]))
						{
							foe[j][0] = -10;
							score += 5;
						}


					}
				}
				if ((bullet[i][0] <= boss_x + 128) && (bullet[i][0] >= boss_x) && (bullet[i][1] <= boss_y + 128) && (bullet[i][1] >= boss_y) && !(boss_off))
				{
					boss_death++;
					bullet[i][2] = 0;
					score += 5;
					if (boss_death == 10)
					{
						boss_off = 1;
						boss_death = 0;

						menu = 6;

					}
				}
				if (bullet[i][0] > 512)
					bullet[i][2] = 0;
			}
		}
		if (boss_off)
		{
			iShowBMP(foe[0][0], foe[0][1], "plane-2.BMP");
			iShowBMP(foe[1][0], foe[1][1], "plane-3.BMP");
			iShowBMP(foe[2][0], foe[2][1], "plane-4.BMP");
			iShowBMP(foe[3][0], foe[3][1], "plane-5.BMP");
		}
		iSetColor(0, 0, 256);


		sprintf_s(str_score, "%d", score);
		iText(74, 597, str_score, GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf_s(str_life, "%d", life);
		iText(229, 597, str_life, GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf_s(str_level, "%d", level);
		iText(440, 597, str_level, GLUT_BITMAP_TIMES_ROMAN_24);
		if (score % 100 == 0 && boss_off)
		{
			life_on = 1;
			life_draw();

		}
		if (life == 0) menu = 6;
		if (life_on == 1 && boss_off)
		{
			iShowBMP(life_x, life_y, "life.BMP");
			life_x--;
			if (life_x <= 0)
				life_on = 0;

			if ((life_x <= gamer_x + 64) && (gamer_x <= life_x) && (life_y <= gamer_y + 64) && (gamer_y <= life_y))
			{
				life_x = -78;
				life_on = 0;
				life++;
			}
		}
		for (j = 0; j < 100; j++)
		{
			if (boss_bullet[j][2] == 1 && !(boss_off))
			{
				iSetColor(255, 255, 255);
				iFilledCircle(boss_bullet[j][0], boss_bullet[j][1], 5, 100);
				boss_bullet[j][0] -= 2;
				if (boss_bullet[j][0] <= 0) boss_bullet[j][2] = 0;
				if (boss_bullet[j][0] <= gamer_x + 64 && boss_bullet[j][0] >= gamer_x  && boss_bullet[j][1] > gamer_y && boss_bullet[j][1] < gamer_y + 64)
				{
					life--;
					boss_bullet[j][2] = 0;
					iDelay(1);
					gamer_x = 0;
					gamer_y = 512;

				}

			}
		}


		if (level_start == 1){
			level_start = 0;
			menu = 10;
			level = 3;
		}
	}

	else if (menu == 10 && level == 3){
		iShowBMP(0, 0, "level-3.bmp");
		iFilledRectangle(load4, 192, 2, 14);
		l++;
		if (l % 4 == 0){
			iFilledRectangle(333, 192, load5, 14);
			load4++;
			load5++;
		}
		if (load4 == 472){
			menu = 11;
			gamer_x = 0;
			gamer_y = 512;
		}
	}

	

	}





/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		bullet_on = 1;

		if (menu == 1){
			//place your codes here	

			if (mx >= 20 && mx <= 183 && my >= 370 && my <= 420){
				menu = 2;
				score = 0;
				life = 3;
				gamer_x = 0;
				gamer_y = 512;
				foe[4][2] = { 0 };
				bullet[150][3] = { 0 };
			}

			else if (mx >= 310 && mx <= 310 + 192 && my >= 220 && my <= 220 + 50)menu = 3;
			else if (mx >= 400 && mx <= 400 + 192 && my >= 370 && my <= 370 + 50 + 50)menu = 4;
			else if (mx >= 50 && mx <= 50 + 126 && my >= 220 && my <= 220 + 50)menu = 5;
			else if (mx >= 210 && mx <= 284 && my >= 70 && my <= 70 + 47)exit(0);



		}
		else if (menu == 4){
			if (mx >= 390 && mx <= 390 + 80 && my >= 40 && my <= 40 + 30)menu = 1;
		}

		else if (menu == 3){
			if (mx >= 390 && mx <= 390 + 80 && my >= 40 && my <= 40 + 30)menu = 1;
		}
		else if (menu == 5){
			if (mx >= 390 && mx <= 470 && my >= 40 && my <= 70){
				menu = 1;
			}
		}
		else if (menu == 6){
			if (mx >= 319 && mx <= 319 + 164 && my >= 82 && my <= 82 + 37) {
				again = 0;
				menu = 1;
				score = 0;
				life = 3;
				gamer_x = 0;
				gamer_y = 512;
				foe[4][2] = { 0 };
				bullet[150][3] = { 0 };




			}
		}
	}


	
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}

}


/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)

{
	if (gettingname == 1) //Game Over & Input Name
	{
		if (key == '\r' && len != 0)
		{
			//if (len == 0){
			//strcpy(leaderboard[10].name, "Nobody");
			//}
			strcpy(leaderboard[10].name, user_name);
			leaderboard[10].mv = score;
			
			sort(leaderboard, leaderboard + 11, cmp);
			gettingname = 0;
			for (int i = 0; i < 11; i++)
				user_name[i] = '\0';
			len = 0;
			menu = 1;
			again = 0;
			menu = 1;
			score = 0;
			life = 3;
			gamer_x = 0;
			gamer_y = 512;
			foe[4][2] = { 0 };
			bullet[150][3] = { 0 };
		}
		else if (key == '\b')
		{
			len--;
			user_name[len] = '\0';
		}
		else if (key == 32) // SpaceBar pressed
		{

		}
		else if (len < 10 && key != '\r')
		{
			user_name[len] = key;
			len++;
		}
	}

	if (key == 'l')
	{
		if (gamer_state[0] == 1)
		{
			gamer_state[1] = 1;
			gamer_state[0] = 0;
		}
	}
	if (key == 'e' && (gamer_state[1] == 1 || gamer_state[2] == 1))
	{
		gamer_state[0] = 1;
		gamer_state[1] = 0;
		gamer_state[2] = 0;

	}
	if (key == 'r')
	{
		if (gamer_state[0] == 1)
		{
			gamer_state[2] = 1;
			gamer_state[0] = 0;
		}
	}
	

	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_RIGHT)
	{
		gamer_x += 10;
		if (gamer_x>384)
			gamer_x = 384;

	}

	if (key == GLUT_KEY_LEFT)
	{
		gamer_x -= 10;
		if (gamer_x<0)
			gamer_x = 0;
	}
	if (key == GLUT_KEY_UP)
	{
		gamer_y += 10;
		if (gamer_y>512)
			gamer_y = 512;
	}
	if (key == GLUT_KEY_DOWN)
	{
		gamer_y -= 10;
		if (gamer_y<0)
			gamer_y = 0;
	}
	if (key == GLUT_KEY_END){
		exit(0);
	}
	//place your codes for other keys here
}


int main()
{

	//place your own initialization codes here. 
	iSetTimer(90000,boss_draw);
	iInitialize(512, 660, "AIR FIGHTER");


	return 0;
}