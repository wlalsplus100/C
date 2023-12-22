#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 3000 // 총 추가 가능한 계정 수
#define MAX_ID_LENGHT 9 // 아이디, 비번 글자 제한 수

char ID[MAX][MAX_ID_LENGHT]; //샘플
char PW[MAX][MAX_ID_LENGHT]; //샘플
char userId[MAX_ID_LENGHT] = { '\0',};
int userIndex = 0;

struct Member {
	char id[MAX_ID_LENGHT];
	char password[MAX_ID_LENGHT];
	char repassword[MAX_ID_LENGHT];
};

void memo();


void datasave(int setting) { //이재영
	FILE* idfp = fopen("id.txt", "r+");
	FILE* pwfp = fopen("pw.txt", "r+");
	char buffer[MAX_ID_LENGHT];
	int cnt = 0;
	if (setting == 1) {
		while (fgets(buffer, MAX, idfp) != NULL) {
			buffer[strcspn(buffer, "\n")] = '\0';
			strcpy(ID[cnt], buffer);
			cnt++;
		}
		cnt = 0;
		while (fgets(buffer, MAX, pwfp) != NULL) {
			buffer[strcspn(buffer, "\n")] = '\0';
			strcpy(PW[cnt], buffer);
			cnt++;
		}
	}
	else if (setting == 0) {
		for (int i = 0; i < sizeof(ID) / sizeof(ID[0]); i++) { //ID의 최대 갯수만큼(3000) 반복함
			if (ID[i][1] == '\0') break; //만약 더 저장된 ID가 없다면 반복을 멈춤
			fprintf(idfp, "%s\n", ID[i]);	//id.txt파일에 쓰기
			fprintf(pwfp, "%s\n", PW[i]);	//pw.txt파일에 쓰기
			fflush(idfp); //저장
			fflush(pwfp); //저장
		}
	}

	fclose(idfp);
	fclose(pwfp);

	return;
}

void signup() { //김도경
	struct Member member;

	printf("Enter your ID : ");
	scanf("%s", member.id);

	for (int i = 0; i < sizeof(ID) / sizeof(ID[0]); i++) {
		if (ID[i][1] == '\0') break;
		if (strcmp(member.id, ID[i])== 0) {
			printf("Duplicated username\n");
			signup();
			return;
		}
	}

	system("cls");

	printf("Enter your Password : ");
	scanf("%s", member.password);

	system("cls");

	printf("Re-enter your password : ");
	scanf("%s", member.repassword);

	while (strcmp(member.password, member.repassword) != 0) {
		system("cls");
		printf("Incorrect password. Please re-enter.\n");


		printf("Enter your Password : ");
		scanf("%s", member.password);

		system("cls");

		printf("Re-enter your Password : ");
		scanf("%s", member.repassword);
	}
	system("cls");
	printf("Member information\n");
	printf("--------------------------\n");
	printf("ID: %s\n", member.id);
	printf("Password: %s\n", member.password);

	//ID, PW배열에 member.id 넣고 member.password 넣기

	for (int i = 0; i <= sizeof(ID) / sizeof(ID[0]); i++) { //ID의 최대 갯수만큼(3000) 반복함
		if (ID[i][1] == '\0') { //만약 ID가 저장되지 않았다면
			strcpy(ID[i], member.id); //ID를 저장함
			strcpy(PW[i], member.password); //같은 인덱스에 비번도 저장함
			break; //만약 저장되었으니 반복을 멈춤
		}
	}
}

void Login() { //박현아
	char id[MAX_ID_LENGHT], pw[MAX_ID_LENGHT];
	char yn;
	int cnt = 0;
	int isLoggedIn = 0;
	printf("plase enter your ID : "); //아이디 입력
	scanf(" %s", id);
	printf("plase enter your PW : "); //비밀번호 입력
	scanf(" %s", pw);

	for (cnt = 0; cnt < sizeof(ID) / sizeof(ID[0]); cnt++) {
		if (strcmp(id, ID[cnt]) == 0) {
			isLoggedIn = 1;
			break; //만약 아이디가 맞는지 확인
		}


	}

	if (!isLoggedIn) {
		system("cls");
		printf("Incorrect ID\n");
		printf("Try again? (y/n)\n");
		scanf(" %c", &yn);
		if (yn == 'y') {
			system("cls");

			Login(); // 로그인 다시 실행
			return;
		}
		else {
			return;
		}
	}

	isLoggedIn = 0;

	for (cnt = 0; cnt < sizeof(PW) / sizeof(PW[0]); cnt++) {
		if (strcmp(pw, PW[cnt]) == 0) {
			isLoggedIn = 1; // 로그인 성공시
			break;
		}
	}

	if (!isLoggedIn) {
		system("cls");
		printf("Incorrect PW\n");
		printf("Try again? (y/n)\n");
		scanf(" %c", &yn);
		if (yn == 'y') {
			system("cls");
			Login(); // 로그인 다시 실행
			return;
		}
		else {
			return;
		}
	}

	system("cls");
	printf("Thank you for using our program.\n==================\n"); //비번, 아이디 둘 다 맞으면 출발하고 id를 return하기
	strcpy(userId, id);
	memo();
	return;
}

void memo() { //박지민
	FILE* fp = fopen("id.txt", "r"); //id 파일을 읽어
	char buffer[MAX] = { 0, }; //읽은 것을 담아둘 문자배열

	fread(buffer, 1, MAX, fp); //전체 읽기
	fclose(fp); //읽었으니 닫기
	char* ptr = strtok(buffer, "\n"); //문자배열에서 \n을 잘라내 앞에 있는 곳의 주소를 ptr에 저장

	int cnt = 0; //id가 몇번째 줄에 있는지 확인
	int stop = 0; //반복문 탈출용
	while (ptr != NULL)       // 자른 문자열이 나오지 않을 때까지 반복
	{

		if (strcmp(userId, ptr) == 0) { // 로그인 된 id와 데이터베이스 id를 비교해서 같은 것을 찾아냄
			stop = 1; // 같은 것을 찾았음
			break; // 같은 것을 찾았으니 반복을 멈춤
		}
		cnt++; // 같은 것을 못찾았으니 다음줄 수로 바꿈
		ptr = strtok(NULL, "\n"); //문자배열에서 \n을 잘라내 앞에 있는 곳의 주소를 ptr에 저장
	}


	if (stop) { //반복문이 멈추면 (같은 것을 찾았다면)
		fp = fopen("memo.txt", "r+");  //test파일을 r+(읽기수정) 모드로 열기
		char data[MAX] = { 0 }; // 한 줄을 담아둘 문자배열 선언

		for (int i = 0; i <= cnt; i++) {
			fgets(data, MAX, fp); // 찾아낸 줄 수 까지 가서 data에 저장함
		}

		printf("%s's memo\n%s", userId, data); // 저장되어 있던 메모 출력


		while (1) {
			char stop; //반복문 탈출 확인용
			printf("==================\nEdit your memo? (y/n)"); //y와 n으로 구분하여 멈출지 수정할지 정함
			scanf(" %c", &stop); // 입력버퍼 오류 줄이기 위해 띄어쓰기
			system("cls");

			if (stop == 'n') break; // n이면 반복 탈출
			else if (stop == 'y') { // y면 수정
				system("cls");
				printf("Enter your memo (Within %d characters) : ", MAX); //3000자 이내 입력받도록 안내
				
				scanf(" %[^\n]", data); //줄바꿈 이전까지 받아서 data에 받음
				fclose(fp); // 아까 열었던 것 닫음
				fp = fopen("memo.txt", "r+"); // 새로 읽기 + 수정으로 열기
				FILE* tempFile = fopen("temp.txt", "w"); // temp파일을 쓰기모드로 열기
				char line[MAX];
				int currentLine = 0;

				while (fgets(line, MAX, fp)) { // line에 한줄을 받아오는데 null이 아닐때까지 반복
					if (currentLine == cnt) { // 만약 우리가 바꾸기로 했던 유저줄이라면
						fprintf(tempFile, "%s\n", data); //data로 받아왔던 입력을 tempfile에 씀
					}
					else {
						fprintf(tempFile, "%s", line); // 바꾸지 않는 유저줄은 이전과 같은 줄을 적음
					}
					currentLine++; // 다음줄로 넘김
				}

				fclose(fp); // 닫기
				fclose(tempFile); //닫기

				remove("memo.txt"); //이전 메모파일 삭제
				if (rename("temp.txt", "memo.txt")) {
					printf("file isn't change!\n");
				}//temp파일을 memo파일로 이름변경
				printf("%s's memo\n%s\n", userId, data); //바뀐 메모를 보여줌
			}
		}
	}
	return;
}




int main() {
	char ls;
	while (1)
	{
		printf("\nLogin? or Signin?(l / s) or end(e): "); //로그인 할 것인지 가입 할 것인지 아니면 끝낼것인지 문기
		scanf(" %c", &ls);
		if (ls == 'e') break; //만약 e면 프로그램 끝내기
		else if (ls == 'l') {
			datasave(1);
			Login(); //l이면 login가기
			datasave(0);
		}
		else if (ls == 's') {
			datasave(1);
			signup();
			datasave(0);
		} //s면 signIn가기
		else {
			return 0;
		}
	}

	return 0;
}

