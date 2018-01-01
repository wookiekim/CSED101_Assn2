#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void print_tutorial();
int check_betting_money(int balance, int betting);
int card_shuffle();
int player_turn(int psum, int dsum);
int dealer_turn(int psum, int dsum);
int judgement(int psum, int dsum, int betting, int turn_end);

int main() {

	int menu;
	int game_no, balance, betting;
	int p1, p2, d1, d2, psum, dsum;
	int turn_end;

	srand(time(NULL));

	while (1) {
		printf("[ ���� ���� ]\n");
		printf("===============================\n");
		printf("1.  ���� ����\n");
		printf("2.  ���� ����\n");
		printf("3.  ����\n");
		printf("===============================\n");
		printf("����:");

		scanf("%d", &menu);

		switch (menu) {
		case 1: {
			print_tutorial();
			break;
		}
		case 2: {
			game_no = 1;
			balance = 10000;

			while (1) {
				printf("\n[���� �ϱ�]\n");
				printf("=====================================================\n");
				printf("===== [����  ����	%d]  [������: %d] =====\n", game_no, balance);
				printf("=====================================================\n");

				do {
					printf("���� �ݾ�: ");
					scanf("%d", &betting);
				} while (!check_betting_money(balance, betting));

				balance -= betting;

				printf("================================================================\n");
				printf("===== [���� ���� %2d]  [������: %5d]  [���� �ݾ�: %4d] =====\n", game_no, balance, betting);
				printf("================================================================\n");

				p1 = card_shuffle();
				Sleep(300);
				printf("Player�� 1��° ī��� %2d�Դϴ�.	#\n", p1);
				
				d1 = card_shuffle();
				Sleep(300);
				printf("				#	Dealer�� 1��° ī��� %2d�Դϴ�.\n", d1);

				do p2 = card_shuffle(); while (p1 == p2 && p1 == 11);
				Sleep(300);
				printf("Player�� 2��° ī��� %2d�Դϴ�.	#\n", p2);

				do d2 = card_shuffle(); while (d1 == d2 && d1 == 11);
				Sleep(300);
				printf("				#	Dealer�� 2��° ī��� %2d�Դϴ�.\n", d2);

				psum = p1 + p2;
				dsum = d1 + d2;

				printf("--------------------------------------------------\n");
				printf("  (Player) %2d <========> (Dealer) %2d\n", psum, dsum);
				printf("--------------------------------------------------\n");

				turn_end = 0;

				if (psum == 21 || dsum == 21)
				goto RESULT;

				psum = player_turn(psum, dsum);
				if (psum > 21) goto RESULT;

				dsum = dealer_turn(psum, dsum);

				turn_end = 1;
			RESULT:

				balance += judgement(psum, dsum, betting, turn_end);

				printf("���� �������� %5d���Դϴ�.\n", balance);
				printf("-------------------------------------------------\n");

				if (balance == 0) {
					printf("�������� �����Ͽ� ������ �̾�� �� �����ϴ�.\n\n");
					break;
				}
				else {
					char regame;
					printf("������ ����Ͻðڽ��ϱ�? (y/n): ");
					scanf(" %c", &regame);

					if (regame == 'y') {
						game_no++;
						continue;
					}
					else break;
				}

			}

			break;
		}
		case 3: {
			return 0;
		}
		default: {
			printf("�ٽ� �����ϼ���\n\n");
			continue;
		}
		}
		
	}

	return 0;
}

void print_tutorial() {
	printf("==========================  ����  ����  ==========================\n");
	printf("������  ī����  ����  21��  �����ų�  21��  ��  �¸��ϴ�  �����̴�.\n");
	printf("�÷��̾��  ������  1~11������  ī�带  �����ϰ�  ����  ��  �ִ�.\n");
	printf("ī�带  �ޱ�  ��  �÷��̾��  ���ϴ� �ݾ���  ��  ��  �ִ�.\n");
	printf("������  ó����  ī�带  �÷��̾� - ����  ������  ��  �徿  ��  ��  �徿���й��Ѵ�.\n");
	printf("��  ��  ��  ����  ī���� ������  21��  ������  �ִ�  ���  �����衯����  �¸��ϰ�  �ȴ�.\n");
	printf("������  �÷��̾  ������  �ƴ�  ���  �÷��̾��  ���µ�  ī�带  ����\n");
	printf("ī�带  ��  ������(Hit) ����(Stand)  �����Ѵ�.\n");
	printf("ī����  ����  21��  �Ѿ��(Bust)  �й��ϰ�  �ǹǷ�  21��  ����  �ʴ�  \n");
	printf("�����  ���� �����  ����  �����̴�.\n");
	printf("�÷��̾  ī�带  ���  ����  ��, ������  ī�带  ��  ������  �����Ѵ�.\n");
	printf("������  ��  ����  17��  ���� ������  ī�带  ����ؼ�  ��  �̾ƾ��Ѵ�.\n");
	printf("�����  Ȯ���Ͽ�, ī��  ����  21�̰ų�  21��  ����  �ʴ�  ū  ����  ����  �����  �̱��  �ȴ�.\n");
	printf("�÷��̾  �̱�  ���  ������  �ݾ���  ��  �踦  �ް�, ����  �Ҵ´�.\n");
	printf("����  ����  ������  ���ºη�  �Ͽ� ���ñ���  �����޴´�.\n");
	printf("==================================================================\n\n");
	return;
}

int check_betting_money(int balance, int betting) {
	if (betting > balance) {
		printf("�����ݺ��� Ů�ϴ�\n");
		return 0;
	}
	else
		return 1;
}

int card_shuffle() {
	return rand() % 11 + 1;
}

int player_turn(int psum, int dsum) {

	char pturn;

	printf("\n\n[ Player's Turn ]\n");
	
	while (1) {
		printf("Hit or Stand? (h/s): ");
		scanf(" %c", &pturn);

		if (pturn == 's') return psum;
		else {
			psum += rand() % 11 + 1;

			printf("--------------------------------------------------\n");
			printf("  (Player) %2d <========> (Dealer) %2d\n", psum, dsum);
			printf("--------------------------------------------------\n");

			if (psum > 21) return psum;
		}
	}
}

int dealer_turn(int psum, int dsum) {

	printf("\n\n[ Dealer's Turn ]\n");

	while (dsum < 17) {
		dsum += rand() % 11 + 1;

		printf("--------------------------------------------------\n");
		printf("  (Player) %2d <========> (Dealer) %2d\n", psum, dsum);
		printf("--------------------------------------------------\n");

		if (dsum > 21) return dsum;
	}

	return dsum;
}

int judgement(int psum, int dsum, int betting, int turn_end) {

	printf("\n\n[Result]\n");
	printf("-------------------------------------------------- \n");

	if (!turn_end) {
		if (psum == dsum && psum == 21) {	//both blackjack
			printf("�ڡڡڡڡڡڡ�  Blackjack  �ڡڡڡڡڡڡ�\n");
			printf("Draw\n");
			printf("���� �ݾ� %4d���� ȹ���ϼ̽��ϴ�.\n", betting);
		}
		else if (psum == 21) {	//player blackjack
			printf("�ڡڡڡڡڡڡ�  Blackjack  �ڡڡڡڡڡڡ�\n");
			printf("Player Wins!\n");
			printf("���� �ݾ� %4d�� �� �� (%d)���� ȹ���ϼ̽��ϴ�.\n", betting, 2*betting);
			betting *= 2;
		}
		else if (dsum == 21) {	//dealer blackjack
			printf("�ڡڡڡڡڡڡ�  Blackjack  �ڡڡڡڡڡڡ�\n");
			printf("Dealer Wins!\n");
			printf("���� �ݾ� %4d�� �Ҿ����ϴ�.\n", betting);
			betting = 0;
		}
		else {	//player bust while hit
			printf("Player Busts.\n");
			printf("Dealer Wins!\n");
			printf("���� �ݾ� %4d�� �Ҿ����ϴ�.\n", betting);
			betting = 0;
		}
	}
	else {
		if (dsum > 21) { //dealer bust
			printf("Dealer Busts.\n");
			printf("Player Wins!\n");
			printf("���� �ݾ� %4d�� �� �� (%d)���� ȹ���ϼ̽��ϴ�.\n", betting, 2 * betting);
			betting *= 2;
		}
		else if (dsum == psum) {
			printf("Draw\n");
			printf("���� �ݾ� %4d���� ȹ���ϼ̽��ϴ�.\n", betting);
		}
		else if (psum > dsum) {
			printf("Player Wins!\n");
			printf("���� �ݾ� %4d�� �� �� (%d)���� ȹ���ϼ̽��ϴ�.\n", betting, 2 * betting);
			betting *= 2;
		}
		else if (dsum > psum) {
			printf("Dealer Wins!\n");
			printf("���� �ݾ� %4d�� �Ҿ����ϴ�.\n", betting);
			betting = 0;
		}
	}
	return betting;
}