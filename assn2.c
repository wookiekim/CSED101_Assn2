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
		printf("[ 블랙잭 게임 ]\n");
		printf("===============================\n");
		printf("1.  게임 설명\n");
		printf("2.  게임 시작\n");
		printf("3.  종료\n");
		printf("===============================\n");
		printf("선택:");

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
				printf("\n[베팅 하기]\n");
				printf("=====================================================\n");
				printf("===== [블랙잭  게임	%d]  [소지금: %d] =====\n", game_no, balance);
				printf("=====================================================\n");

				do {
					printf("베팅 금액: ");
					scanf("%d", &betting);
				} while (!check_betting_money(balance, betting));

				balance -= betting;

				printf("================================================================\n");
				printf("===== [블랙잭 게임 %2d]  [소지금: %5d]  [베팅 금액: %4d] =====\n", game_no, balance, betting);
				printf("================================================================\n");

				p1 = card_shuffle();
				Sleep(300);
				printf("Player의 1번째 카드는 %2d입니다.	#\n", p1);
				
				d1 = card_shuffle();
				Sleep(300);
				printf("				#	Dealer의 1번째 카드는 %2d입니다.\n", d1);

				do p2 = card_shuffle(); while (p1 == p2 && p1 == 11);
				Sleep(300);
				printf("Player의 2번째 카드는 %2d입니다.	#\n", p2);

				do d2 = card_shuffle(); while (d1 == d2 && d1 == 11);
				Sleep(300);
				printf("				#	Dealer의 2번째 카드는 %2d입니다.\n", d2);

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

				printf("현재 소지금은 %5d원입니다.\n", balance);
				printf("-------------------------------------------------\n");

				if (balance == 0) {
					printf("소지금이 부족하여 게임을 이어나갈 수 없습니다.\n\n");
					break;
				}
				else {
					char regame;
					printf("게임을 계속하시겠습니까? (y/n): ");
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
			printf("다시 선택하세요\n\n");
			continue;
		}
		}
		
	}

	return 0;
}

void print_tutorial() {
	printf("==========================  게임  설명  ==========================\n");
	printf("블랙잭은  카드의  합이  21에  가깝거나  21일  때  승리하는  게임이다.\n");
	printf("플레이어와  딜러는  1~11사이의  카드를  랜덤하게  뽑을  수  있다.\n");
	printf("카드를  받기  전  플레이어는  원하는 금액을  걸  수  있다.\n");
	printf("딜러가  처음에  카드를  플레이어 - 딜러  순으로  한  장씩  총  두  장씩을분배한다.\n");
	printf("이  때  두  장의  카드의 총합이  21인  선수가  있는  경우  ‘블랙잭’으로  승리하게  된다.\n");
	printf("딜러와  플레이어가  블랙잭이  아닌  경우  플레이어는  오픈된  카드를  보고\n");
	printf("카드를  더  받을지(Hit) 말지(Stand)  결정한다.\n");
	printf("카드의  합이  21이  넘어가면(Bust)  패배하게  되므로  21를  넘지  않는  \n");
	printf("가까운  수를 만드는  것이  관건이다.\n");
	printf("플레이어가  카드를  모두  뽑은  후, 딜러가  카드를  더  뽑을지  결정한다.\n");
	printf("딜러는  총  합이  17을  넘지 않으면  카드를  계속해서  더  뽑아야한다.\n");
	printf("결과를  확인하여, 카드  합이  21이거나  21을  넘지  않는  큰  수를  가진  사람이  이기게  된다.\n");
	printf("플레이어가  이길  경우  배팅한  금액의  두  배를  받고, 지면  잃는다.\n");
	printf("같은  수가  나오면  무승부로  하여 베팅금을  돌려받는다.\n");
	printf("==================================================================\n\n");
	return;
}

int check_betting_money(int balance, int betting) {
	if (betting > balance) {
		printf("소지금보다 큽니다\n");
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
			printf("★★★★★★★  Blackjack  ★★★★★★★\n");
			printf("Draw\n");
			printf("베팅 금액 %4d원을 획득하셨습니다.\n", betting);
		}
		else if (psum == 21) {	//player blackjack
			printf("★★★★★★★  Blackjack  ★★★★★★★\n");
			printf("Player Wins!\n");
			printf("베팅 금액 %4d의 두 배 (%d)원을 획득하셨습니다.\n", betting, 2*betting);
			betting *= 2;
		}
		else if (dsum == 21) {	//dealer blackjack
			printf("★★★★★★★  Blackjack  ★★★★★★★\n");
			printf("Dealer Wins!\n");
			printf("베팅 금액 %4d을 잃었습니다.\n", betting);
			betting = 0;
		}
		else {	//player bust while hit
			printf("Player Busts.\n");
			printf("Dealer Wins!\n");
			printf("베팅 금액 %4d을 잃었습니다.\n", betting);
			betting = 0;
		}
	}
	else {
		if (dsum > 21) { //dealer bust
			printf("Dealer Busts.\n");
			printf("Player Wins!\n");
			printf("베팅 금액 %4d의 두 배 (%d)원을 획득하셨습니다.\n", betting, 2 * betting);
			betting *= 2;
		}
		else if (dsum == psum) {
			printf("Draw\n");
			printf("베팅 금액 %4d원을 획득하셨습니다.\n", betting);
		}
		else if (psum > dsum) {
			printf("Player Wins!\n");
			printf("베팅 금액 %4d의 두 배 (%d)원을 획득하셨습니다.\n", betting, 2 * betting);
			betting *= 2;
		}
		else if (dsum > psum) {
			printf("Dealer Wins!\n");
			printf("베팅 금액 %4d을 잃었습니다.\n", betting);
			betting = 0;
		}
	}
	return betting;
}