#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX 3000 // �� �߰� ������ ���� ��
#define MAX_ID_LENGHT 9 // ���̵�, ��� ���� ���� ��

char ID[MAX][MAX_ID_LENGHT] = { "asdf", "qwer", "zxcv" }; //����
char PW[MAX][MAX_ID_LENGHT] = { "sdfg", "rtyu", "ghjk" }; //����
char userId[MAX_ID_LENGHT] = { 0, };

struct Member {
	char id[MAX_ID_LENGHT];
	char password[MAX_ID_LENGHT];
	char repassword[MAX_ID_LENGHT];
};

void memo();

void signup() {
	struct Member member;

	printf("ȸ�� ID�� �Է��ϼ���: ");
	scanf("%s", member.id);

	printf("��й�ȣ�� �Է��ϼ���: ");
	scanf("%s", member.password);

	printf("��й�ȣ�� �ٽ� �Է��ϼ���: ");
	scanf("%s", member.repassword);

	while (strcmp(member.password, member.repassword) != 0) {
		printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���.\n");

		printf("��й�ȣ�� �Է��ϼ���: ");
		scanf("%s", member.password);

		printf("��й�ȣ�� �ٽ� �Է��ϼ���: ");
		scanf("%s", member.repassword);
	}

	printf("ȸ�� ����\n");
	printf("--------------------------\n");
	printf("ID: %s\n", member.id);
	printf("��й�ȣ: %s\n", member.password);
}

void Login() {
	char id[MAX_ID_LENGHT], pw[MAX_ID_LENGHT];
	char yn;
	int cnt = 0;
	int isLoggedIn = 0;
	printf("plase enter your ID : "); //���̵� �Է�
	scanf(" %s", id);
	printf("plase enter your PW : "); //��й�ȣ �Է�
	scanf(" %s", pw);
	for (cnt = 0; cnt < sizeof(ID) / sizeof(ID[0]); cnt++) {
		if (strcmp(id, ID[cnt]) == 0) {
			isLoggedIn = 1;
			break; //���� ���̵� �´��� Ȯ��
		}


	}

	if (!isLoggedIn) {
		printf("Incorrect ID\n");
		printf("Try again? (y/n)\n");
		scanf(" %c", &yn);
		if (yn == 'y') {
			Login(); // �α��� �ٽ� ����
			return;
		}
		else {
			return;
		}
	}
	 
	isLoggedIn = 0;

	for (cnt = 0; cnt < sizeof(PW) / sizeof(PW[0]); cnt++) {
		if (strcmp(pw, PW[cnt]) == 0) {
			isLoggedIn = 1; // �α��� ������
			break;
		}
	}

	if (!isLoggedIn) {
		printf("Incorrect PW\n");
		printf("Try again? (y/n)\n");
		scanf(" %c", &yn);
		if (yn == 'y') {
			Login(); // �α��� �ٽ� ����
			return;
		}
		else {
			return;
		}
	}

	 
	printf("Let's go\n"); //���, ���̵� �� �� ������ ����ϰ� id�� return�ϱ�
	strcpy(userId, id);
	memo();
	return;
}

void memo() {
	FILE* fp = fopen("id.txt", "r"); //id ������ �о�
	char buffer[MAX] = { 0, }; //���� ���� ��Ƶ� ���ڹ迭

	fread(buffer, 1, MAX, fp); //��ü �б�
	fclose(fp); //�о����� �ݱ�
	char* ptr = strtok(buffer, "\n"); //���ڹ迭���� \n�� �߶� �տ� �ִ� ���� �ּҸ� ptr�� ����

	int cnt = 0; //id�� ���° �ٿ� �ִ��� Ȯ��
	int stop = 0; //�ݺ��� Ż���
	while (ptr != NULL)       // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{

		if (strcmp(userId, ptr) == 0) { // �α��� �� id�� �����ͺ��̽� id�� ���ؼ� ���� ���� ã�Ƴ�
			stop = 1; // ���� ���� ã����
			break; // ���� ���� ã������ �ݺ��� ����
		}
		cnt++; // ���� ���� ��ã������ ������ ���� �ٲ�
		ptr = strtok(NULL, "\n"); //���ڹ迭���� \n�� �߶� �տ� �ִ� ���� �ּҸ� ptr�� ����
	}


	if (stop) { //�ݺ����� ���߸� (���� ���� ã�Ҵٸ�)
		fp = fopen("memo.txt", "r+");  //test������ r+(�б����) ���� ����
		char data[MAX] = { 0 }; // �� ���� ��Ƶ� ���ڹ迭 ����

		for (int i = 0; i <= cnt; i++) {
			fgets(data, MAX, fp); // ã�Ƴ� �� �� ���� ���� data�� ������
		}

		printf("%s�� �޸�\n%s", userId, data); // ����Ǿ� �ִ� �޸� ���


		while (1) {
			char stop; //�ݺ��� Ż�� Ȯ�ο�
			printf("�����Ͻðڽ��ϱ�? (y/n)"); //y�� n���� �����Ͽ� ������ �������� ����
			scanf(" %c", &stop); // �Է¹��� ���� ���̱� ���� ����

			if (stop == 'n') break; // n�̸� �ݺ� Ż��
			else if (stop == 'y') { // y�� ����
				printf("�޸� �Է��ϼ��� (%d �̳�) : ", MAX); //3000�� �̳� �Է¹޵��� �ȳ�
				scanf(" %[^\n]", data); //�ٹٲ� �������� �޾Ƽ� data�� ����
				fclose(fp); // �Ʊ� ������ �� ����
				fopen("memo.txt", "r+"); // ���� �б� + �������� ����
				FILE* tempFile = fopen("temp.txt", "w"); // temp������ ������� ����
				char line[MAX];
				int currentLine = 0;

				while (fgets(line, MAX, fp)) { // line�� ������ �޾ƿ��µ� null�� �ƴҶ����� �ݺ�
					if (currentLine == cnt) { // ���� �츮�� �ٲٱ�� �ߴ� �������̶��
						fprintf(tempFile, "%s\n", data); //data�� �޾ƿԴ� �Է��� tempfile�� ��
					}
					else {
						fprintf(tempFile, "%s", line); // �ٲ��� �ʴ� �������� ������ ���� ���� ����
					}
					currentLine++; // �����ٷ� �ѱ�
				}

				fclose(fp); // �ݱ�
				fclose(tempFile); //�ݱ�

				remove("memo.txt"); //���� �޸����� ����
				rename("temp.txt", "memo.txt"); //temp������ memo���Ϸ� �̸�����
				printf("%s�� �޸�\n%s\n", userId, data); //�ٲ� �޸� ������
			}
		}
	}
	return;
}


//int main() {
//	memo("user4");
//	return 0;
//}

int main() {
	char ls;
	while (1)
	{
		printf("\nLogin? or Signin?(l / s) or end(e): "); //�α��� �� ������ ���� �� ������ �ƴϸ� ���������� ����
		scanf(" %c", &ls);
		if (ls == 'e') break; //���� e�� ���α׷� ������
		else if (ls == 'l')  Login(); //l�̸� login����
		else if (ls == 's') signup(); //s�� signIn����
	}

	return 0;
}

