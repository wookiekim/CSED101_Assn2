/* 20150630 기계공학과 김승욱 Assignment 2 */

#include <stdio.h>
#include <Windows.h>//Sleep 함수를 사용하기위한 헤더파일
#include <stdlib.h>//rand함수를 사용하기 위한 헤더파일
#include <time.h>//srand함수에 time(null)시드를 주기 위한 헤더파일

void print_initial();//첫 옵션을 출력해주는 함수
void print_tutorial();//튜토리얼을 출력해준 후, 다시 첫 옵션을 출력해주는 함수
int check_betting_money(int *x);//입력된 베팅값이 현재 소지금보다 낮은지 체크한 후 반환하는 함수
int card_shuffle();//1~11사이의 숫자를 랜덤으로 뽑아주는 함수
int player_turn(int x,int y);//플레이어의 턴을 실행해주는 함수. Hit/Stand기능을 포함하고 있다.
int dealer_turn(int x,int y);//딜러의 턴을 실행해주는 함수다. 
int judgement(int x, int y,int m);//결과적으로 누가 이겼는지 판정하고 결과에 따라 베팅금액을 돌려주거나, 잃거나, 두배를 얻게 된다.

int main (void)
{
	int game_no=1,cash=10000,opt,betting;
	int pl1,pl2,dl1,dl2,psum,dsum,winning;
	char yesno;//프로그램 내에서 필요한 여러 변수들을 정의하였다.

	srand((unsigned int)time(NULL));//랜덤함수를 뽑기 위한 시드를 제공해주는 함수이다.

	print_initial();//첫 옵션을 출력해준다.

	while(1)//아래의 선택에 따라 다시 첫화면을 보여야 할 때가 있는데, 그때를 위하여 main에 남아있는 나머지 부분을 전체 무한루프에 포함시킨다.
	{
		scanf("%d",&opt);//첫 옵션의 선택지를 입력받는다.

		switch(opt){//선택지에 따른 결과를 정해준다.
			case 1://튜토리얼을 보여주고, 다시 첫 실행페이지를 출력해준다.
				print_tutorial();
				print_initial();
				continue;//다시 선택지를 입력받기 위해, while(1)로 돌려보낸다,

			case 2://게임을 시작하는 옵션이다.

				while(1){//게임의 연속플레이를 가능하게 하기 위해, case2의 전체 내용을 무한반복문에 넣는다.

				printf("\n[ 베팅 하기 ]\n");
				printf("===========================================================\n");
				printf("===== [ 블랙잭 게임 %d ] [ 소지금: %d ]\n",game_no,cash);
				printf("===========================================================\n");
				betting=check_betting_money(&cash);//betting 끝

				printf("\n================================================================\n");
				printf("===== [ 블랙잭 게임 %d ] [ 소지금: %d ] [베팅 금액: %d] ======\n",game_no++,cash,betting);
				printf("================================================================\n");//게임 준비 완료

				printf("Player의 1번째 카드는 %d 입니다.    #\n",pl1=card_shuffle());
				printf("                                    # Dealer의 1번째 카드는 %d입니다.\n",dl1=card_shuffle());//플레이어와 딜러에게 각각 카드 1장씩 배분한다.

				while(1){//첫카드가 11인경우 두번째 카드가 11이 나오지 않도록 조건문을 추가하였다. Sleep을 card_shuffle안에 추가할 경우 0.3n초가 걸릴수 있기에 밖으로 빼내었다.
					pl2=card_shuffle();
					if(pl1==11 && pl2==11)
						continue;
					else{
						printf("Player의 2번째 카드는 %d 입니다.    #\n",pl2);
						break;
					}
				}
				while(1){//첫카드가 11인경우 두번째 카드가 11이 나오지 않도록 조건문을 추가하였다. Sleep을 card_shuffle안에 추가할 경우 0.3n초가 걸릴수 있기에 밖으로 빼내었다.
						dl2=card_shuffle();
					if(dl1==11 && dl2==11)
						continue;
					else{
						printf("                                    # Dealer의 2번째 카드는 %d입니다.\n",dl2);
						break;
						}
				}//플레이어와 딜러에게 각각 두번째 카드를 배분하지만, 첫카드가 11일때 두번째 카드도 11일때를 대비하여 조건문을 추가하였다.
				printf("-------------------------------------------------- \n");
				printf("(Player) %d <========> (Dealer) %d \n",psum=pl1+pl2,dsum=dl1+dl2);
				printf("-------------------------------------------------- \n");//카드배분이 끝난 뒤의 플레이어와 딜러의 각 카드값의 합을 보여준다.

				if(psum==21 || dsum==21){//카드 배분이 끝난 후 합이 21일경우 블랙잭인 상황을 위하여 조건물을 넣었다. 21이 아니라면 상관없기에 이 if에 대응하는 else는 없다.
					printf("[Result]\n");
					printf("-------------------------------------------------- \n");
					printf("★★★★★★★ Blackjack ★★★★★★★ \n");
					
					winning=judgement(psum,dsum,betting);

					printf("현재 소지금은 %d원입니다.\n",cash+=winning);
					printf("------------------------------------------------- \n");

						if(cash>0){//소지금이 남아있을 경우이다.
							printf("게임을 계속하겠습니까? (y/n):");
							scanf(" %c",&yesno);

							if(yesno=='y'){//게임을 계속할때의 조건문이다.
								continue;//다시 case2의 반복문으로 돌아가서 게임을 시작한다. 
							}
							else{//n을 입력받았을때의 상황이지만, y혹은n 을 제외한 입력은 고려하지 말라고 하여서 비교적 편하게 작성하였다.
								print_initial();
								game_no=1,cash=10000;
								break;//case 2의 반복문을 빠져나가고, 다시 첫 옵션을 출력해준다.
							}
							
				}
						else{//소지금이 0일때의 경우이다.
							printf("소지금이 부족하여 게임을 이어나갈 수 없습니다.\n\n");
							print_initial();
							game_no=1,cash=10000;
							break;//또한 case 2의 반복문을 빠져나가고, 다시 첫 옵션을 출력해준다.
						}
				}
					

				printf("\n\n[Player's Turn]\n");//블랙잭이 나오지 않았다면 바로 플레이어의 턴이 된다.
				psum=player_turn(psum,dsum);//플레이어 턴을 진행하면서 변하는 플레이어의 카드합을 반환해준다.

						if(psum>21){//hit or stand중 카드합이 21이 넘어갔을때의 상황이다. /
					printf("[Result]\n");
					printf("-------------------------------------------------- \n");
					
					winning=judgement(psum,dsum,betting);//판정을 위해 judgement로 넘어간다.

					printf("현재 소지금은 %d원입니다.\n",cash+=winning);
					printf("------------------------------------------------- \n");

						if(cash>0){//위와같은 조건문들이다.
							printf("게임을 계속하겠습니까? (y/n):");
							scanf(" %c",&yesno);

							if(yesno=='y'){
								continue;
							}
							else{
								print_initial();
								game_no=1,cash=10000;
								break;
							}
				}
						else{
							printf("소지금이 부족하여 게임을 이어나갈 수 없습니다.\n\n");
							print_initial();
							game_no=1,cash=10000;
							break;
						}
				}

				printf("\n[Dealer's Turn]\n");//플레이어의 턴에서 플레이어의 카드합이 21이 되거나 넘지 않았을때 stand로 턴을 마쳤다면, 딜러의 턴으로 넘어오게된다.
				dsum=dealer_turn(psum,dsum);//딜러의 턴에서 변하는 딜러의 카드합을 반환해준다.
				
				printf("\n[Result]\n");//모든 턴이 끝이 났으니, 이 곳에서는 당연한 [Result]항목으로 온다.
				printf("--------------------------------------------------\n");
				winning=judgement(psum,dsum,betting);

					printf("현재 소지금은 %d원입니다.\n",cash+=winning);
					printf("------------------------------------------------- \n");

						if(cash>0){
							printf("게임을 계속하겠습니까? (y/n):");
							scanf(" %c",&yesno);

							if(yesno=='y'){
								continue;
							}
							else{
								print_initial();
								game_no=1,cash=10000;
								break;
							}
				}
						else{
							printf("소지금이 부족하여 게임을 이어나갈 수 없습니다.\n\n");
							print_initial();
							game_no=1,cash=10000;
							break;
						}

				}
				break;//사실 이곳까지 올 일은 없지만, switch의 형식에 걸맞는 break 이다.
			case 3://게임을 종료하는 선택지이다.
				return 0;//프로그램을 종료한다.

			default://선택지에서 1,2,3중 다른것을 입력하였을 경우이다.
				printf("다시 선택하세요 \n\n");
				print_initial();
				continue;//다시 선택하게 한다. While문으로 돌아간다.
		}
	}

	return 0;
	}//main 함수의 끝이다. 이후로는 사용자정의 함수이다. 각각의 설명은 위에 해 놓았으니, 구성요소에만 주석을 달기로 하였다.

void print_tutorial()
{
	printf("==========================게임설명========================== \n");
	printf("블랙잭은 카드의 합이 21에 가깝거나 21일 때 승리하는 게임이다.\n");
	printf("플레이어와 딜러는 1~11사이의 카드를 랜덤하게 뽑을 수 있다. 카드를 받기 전 플레이어는 원하는 금액을 걸 수 있다.\n");
	printf("딜러가 처음에 카드를 플레이어-딜러 순으로 한 장씩 총 두 장씩을 분배한다. 이 때 두 장의 카드의 총합이 21인 선수가 있는 경우 ‘블랙잭’으로 승리하게 된다.\n");
	printf("딜러와 플레이어가 블랙잭이 아닌 경우 플레이어는 오픈된 카드를 보고 카드를 더 받을지(Hit) 말지(Stand) 결정한다. 카드의 합이 21이 넘어가면(Bust) 패배하게 되므로 21를 넘지 않는 가까운 수를 만드는 것이 관건이다.\n");
	printf("플레이어가 카드를 모두 뽑은 후, 딜러가 카드를 더 뽑을지 결정한다. 딜러는 총 합이 17을 넘지 않으면 카드를 계속해서 더 뽑아야한다.\n");
	printf("결과를 확인하여, 카드 합이 21이거나 21을 넘지 않는 큰 수를 가진 사람이 이기게 된다.\n");
	printf("플레이어가 이길 경우 배팅한 금액의 두 배를 받고, 지면 잃는다. 같은 수가 나오면 무승부로 하여 베팅금을 돌려받는다.\n");
	printf("============================================================= \n\n");
}

void print_initial()
{
	printf("[ 블랙잭 게임 ]\n");
	printf("=============================== \n");
	printf(" 1. 게임 설명 \n");
	printf(" 2. 게임 시작  \n");
	printf(" 3. 종료 \n");
	printf("=============================== \n");
	printf(" 선택:");
}
int check_betting_money(int *x)
{
	int bet;//입력받는 값을 저장해주는 변수이다.
	
	while(1){
	printf("베팅 금액:");
	scanf("%d",&bet);
	
	if(bet<=*x){//call by address로 소지금을 입력받았다. 이 함수내에서 소지금의 변화도 직접적으로 바로 일어난다.이는 소지금보다 적은 베팅금액을 적었을 경우이다.
		*x-=bet;
		return bet;
		break;//소지금에서 베팅금액을 차감하고, 그 값을 반환한다.
	}
	else{//입력값이 소지금보다 클 경우이다.
		printf("소지금보다 큽니다.\n");
		continue;//다시 반복문으로 돌아가 베팅금액을 입력받도록 한다.
	}
	}
}
int card_shuffle()
{
	int range=(11-1)+1;
	Sleep(300);
	return rand()% range+1;//1과 11사이의 랜덤한 숫자를 배출한다.
}
int player_turn(int x, int y)
{
	char choice;//플레이어의 선택지를 입력받는 변수이다. h(hit)혹은 s(stand)만 입력된다고 가정한다.

	while(1){//hit을한 후 카드합이 21이 되지 않을경우에는 다시 선택권이 주어지기에, 무한반복문안에 넣었다.
	printf("Hit or Stand?(h/s):");
	scanf(" %c", &choice);

	switch(choice){
	 case 'h':{
		 x+=card_shuffle();
		 
		printf("-------------------------------------------------- \n");
		printf("(Player) %d <========> (Dealer) %d \n",x,y);
		printf("-------------------------------------------------- \n");

		if(x==21 || x>21)
			return x;//hit일때에는 기존의 플레이어 카드값에 또다시 랜덤숫자를 추가하여 출력해낸다. 카드합이 21이거나 넘는다면 자동으로 카드합값을 반환한다.
		else
			continue;//카드합이 21이 되지 않았다면 다시 선택권을 받도록 반복문으로 돌려보낸다.
			  }
	 case 's':
		 return x;//stand를 입력하였다면 그때까지의 카드합을 반환한다.
	}
	break;
	}
}
int dealer_turn(int x,int y)
{
	while(1){//딜러의 카드합이 17이하일때는 무조건 카드를 추가하므로, 무한 반복문 내에 넣어준다.
	if(y<17){
		y+=card_shuffle();
	
		printf("-------------------------------------------------- \n");
		printf("(Player) %d <========> (Dealer) %d \n",x,y);
		printf("-------------------------------------------------- \n");

		continue;//카드합이 17이하일때에는 또다시 랜덤숫자를 카드합에 추가한 후 출력한다. 그 후 또다시 17을 넘는지 체크하기위해 반복문으로 돌려보낸다.
	}
	else 
		return y;//카드합이 17이거나 17을 넘었을때에는 최종적인 딜러의 카드값을 반환한다.
	break;
	}
	
}
int judgement(int x, int y,int m)
{
	int winning;//게임의 결과에 따른 상금을 입력받는 변수이다.

	if(x>21){//플레이어의 카드합이 21을 넘었을 경우이다.
		printf("Player busts.\n");
		printf("Dealer Wins!\n");
		printf("베팅 금액 %d원을 잃었습니다.",m);
		return 0;//버스트를 한 후, 졌을 경우에는 그저 베팅금액만큼을 잃기 때문에 소지금에는 변화가 생기지 않으니 0을 반환한다.
	}
	else if(y>21){//딜러의 카드합이 21을 넘었을 경우이다.
		printf("Dealer busts.\n");
		printf("Player Wins!\n");
		printf("베팅 금액 %d의 두 배 (%d)를 획득하셨습니다.\n",m,winning=2*m);
		return winning;//버스트를 한 후, 이겼을 경우에는 베팅금액의 두배를 얻기때문에 베팅금액의 두배를 반환한다.
	}
	else if(y==x){//플레이어와 딜러의 카드합이 같을 경우이다.
		printf("Draw\n");
		printf("베팅 금액 %d원을 획득하셨습니다.",m);
		return m;//이때에는 승자도 패자도 없으니 베팅한만큼의 금액을 다시 얻게된다.
	}
	else if(x>y || x==21){//플레이어의 카드합이 21이거나 딜러의 카드합을 넘었을 경우이다. 블랙잭일때를 포함하고 있다.
		printf("Player Wins!\n");
		printf("베팅 금액 %d의 두 배 (%d)를 획득하셨습니다.\n",m,winning=2*m);
		return winning;//이겼을 경우에는 베팅금액의 두배를 얻기 때문에 베팅금액의 두배를 반환한다.
	}
	else if(y>x || y==21){//딜러의 카드합이 21이거나 플레이어의 카드합을 넘었을 경우이다. 블랙잭일때를 포함하고 있다.
		printf("Dealer Wins!\n");
		printf("베팅 금액 %d원을 잃었습니다.",m);
		return 0;//졌을때이니 상금은 없다.
	}
}

