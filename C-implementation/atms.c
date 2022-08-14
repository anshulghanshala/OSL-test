
#include <stdio.h>
#include <string.h>
void atm_choice();
void user_account();
void file_read();
void check_credentials();
void services();
void updateBalance();
void deposit();
void withdrawal();
void transfer();

int t = 0;
char toWrite[30];
char *stringArrays[2];
char masteraccountname [21];
char masteraccountnumber[17];
char masterpassword [7];
char masterBalance[15];
char sign;
char updatedbalance[15];
int atm;
char money[7];
// unsigned long long useraccount;
// int userpwd;
char useraccount[17];
char receiveraccount[17];
char userpwd[7];
char service;

int main()
{
    printf("OSL Bank \n");
    printf("Welcome \n"); 
    atm_choice();
    return 0; 
}



void continueFn() {
	printf("Press Y to continue: \n");
	printf("Press N to exit: \n");
	char reply;
	scanf(" %c", &reply);
	if (reply == 'Y') {
		atm_choice();
	}
}

int compareAccountNumber(){
	for(int i = 0; i < 16; i++){
		if(masteraccountnumber[i] != useraccount[i]){
			return 0;
		}
	}
	return 1;
}

int compareAccountPass(){
	for(int i = 0; i < 6; i++){
		if(masterpassword[i] != userpwd[i]){
			return 0;
		}
	}
	return 1;
}

void file_read()
{
    FILE * fp;
    int test;
    int bufferLength=59;
    char buffer[bufferLength];

    fp=fopen("master.txt","r");
    int i=0;
	int accountFound = 0;
    while((fgets(buffer, bufferLength, fp))!=NULL) 
    {
        buffer[strcspn(buffer, "\r\n")] = 0;
		// printf("%s", buffer);
        // stringArrays[i] = strndup(buffer, bufferLength);
		// printf("\nRow num %d: %s", i, stringArrays[i]);
        int index=0,j=0, k=0, l=0, m=0;
        for(index=0; index<58;index++)
        {
            if (index<20){
                masteraccountname[j]=buffer[index];
                j++;
            }
            else if (index<36){
                masteraccountnumber[k]=buffer[index];
                k++;
            }
            else if (index<42){
                masterpassword[l]=buffer[index];
                l++;
            } 
            else if(index == 42){
				sign=buffer[index];
            }else{
				masterBalance[m] = buffer[index];
				m++;
			}
        } 
		accountFound = compareAccountPass() && compareAccountNumber();
        if (accountFound) {
			check_credentials();
			break;
		}
    }
	if (accountFound == 0) check_credentials();
    fclose(fp);
 }

void atm_choice()
{   
	int ch;
    
    printf("Please Choose the ATM \n");
    printf("Press 1 for ATM 711 \n");
    printf("Press 2 for ATM 713 \n");
    scanf("%d",&ch);
    if(ch==1)
    {   
		atm = 1;
        user_account();
    }
    else if(ch==2)
    {
		atm = 2;
        user_account();
    }
    else
    {
        printf("Invalid Input \n");
        atm_choice(ch);

    }
    
}


void user_account()
{
    printf("Enter Account Number \n");
    scanf("%s",useraccount);
    printf("Enter Password\n");
    scanf("%s", userpwd);

    file_read();
}

void check_credentials()
{
	if (compareAccountNumber() == 0) {
		printf("%s \n", useraccount);
		printf("INVALID ACCOUNT/PASSWORD\n");
		user_account();
	} else if (compareAccountPass() == 0) {
		printf("%s \n", userpwd);
		printf("INVALID ACCOUNT/PASSWORD\n");
		user_account();
	} else {
        if (sign == '+'){
			services();
		}
        else if (sign == '-')
        {
            printf("\nNEGATIVE REMAINS TRANSACTION ABORT\n");
            atm_choice();
        }
    }
}

void services()
{
    printf ("\nPLEASE CHOOSE YOUR SERVICE");
    printf ("\nPLEASE D FOR DEPOSIT");
    printf ("\nPLEASE W FOR WITHDRAWAL");
    printf ("\nPLEASE T FOR TRANSFER\n");
    scanf(" %c",&service);
    if (service == 'D')
    deposit();
    else if (service == 'W')
    withdrawal();
    else if (service == 'T')
    transfer();
    else 
    {
    printf("INVALID-INPUT");
    services();
    }
}

void deposit(){
	int flag1 = 0;
	char actAmt[7], amount[7];
	do {
		printf ("AMOUNT =>\n");
		scanf("%s", amount);
		if (amount[0] != '-') flag1= 1;
		else {
			printf ("INVALID AMOUNT\n");
		}
	} while (flag1 == 0);
	int size = 0;
	for (int i = 0; i < 7; i++) {
		if ((amount[i] >= '0' && amount[i] <= '9') || amount[i] == '.') {
			size++;
		} 
	}
	for (int i = size - 1, j = 6; i >= 0; i--) {
		if (amount[i] != '.') {
			// printf("Yhaa");
			actAmt[j] = amount[i];
			j--;
		}	
	}
	for(int i = 0; i < 7; i++) {
		if (actAmt[i] < '0' || actAmt[i] > '9') actAmt[i] = '0';
	}

	int i = 0;
	for(int j = 0; j < 16; j++){
		toWrite[i] = useraccount[j];
		i++;
	}
	toWrite[i] = 'D';
	i++;
	for(int j = 0; j < 7; j++){
		toWrite[i] = actAmt[j];
		i++;
	}

	t++;
	char timeSt[5];
	int currT = t, k = 4;
	while(currT != 0 && k >=0){
		timeSt[k] = '0' + currT % 10;
		currT /= 10; 
		k--;
	}
	
	for(int j =0; j < 5; j++, i++) {
		if (timeSt[j] <'0' || timeSt[j] > '9') {
			toWrite[i] = '0';
		} else {
			toWrite[i] = timeSt[j];
		}
	}
	toWrite[i] = '\n';
	
	FILE *fp;
	if(atm == 1){
		fp = fopen("trans711.txt", "a+");
	}else{
		fp = fopen("trans713.txt", "a+");
	}
	fwrite(toWrite, 30, 1, fp);
	fclose(fp);
	continueFn();
}

void withdrawal() {
	int flag1 = 0;
	char actAmt[7], amount[7];
	do {
		printf ("AMOUNT=>\n");
		scanf("%s", amount);
		if (amount[0] != '-') flag1= 1;
		else {
			printf ("INVALID AMOUNT\n");
		}
	} while (flag1 == 0);
	int size = 0;
	for (int i = 0; i < 7; i++) {
		if ((amount[i] >= '0' && amount[i] <= '9') || amount[i] == '.') {
			size++;
		} 
	}
	for (int i = size - 1, j = 6; i >= 0; i--) {
		if (amount[i] != '.') {
			actAmt[j] = amount[i];
			j--;
		}	
	}
	for(int i = 0; i < 7; i++) {
		if (actAmt[i] < '0' || actAmt[i] > '9') actAmt[i] = '0';
	}

	int i = 0;
	for(int j = 0; j < 16; j++){
		toWrite[i] = useraccount[j];
		i++;
	}
	toWrite[i] = 'W';
	i++;
	for(int j = 0; j < 7; j++){
		toWrite[i] = actAmt[j];
		i++;
	}

	t++;
	char timeSt[5];
	int currT = t, k = 4;
	while(currT != 0 && k >=0){
		timeSt[k] = '0' + currT % 10;
		currT /= 10; 
		k--;
	}
	
	for(int j =0; j < 5; j++, i++) {
		if (timeSt[j] <'0' || timeSt[j] > '9') {
			toWrite[i] = '0';
		} else {
			toWrite[i] = timeSt[j];
		}
	}
	toWrite[i] = '\n';
	
	FILE *fp;
	if(atm == 1){
		fp = fopen("trans711.txt", "a+");
	}else{
		fp = fopen("trans713.txt", "a+");
	}
	fwrite(toWrite, 30, 1, fp);
	fclose(fp);
	continueFn();
}

int isSameAccountForTransfer() {
	for(int i = 0; i < 16; i++){
		if(useraccount[i] != receiveraccount[i]){
			return 0;
		}
	}
	return 1;
}

int compareRAccountNumber(){
	for(int i = 0; i < 16; i++){
		if(masteraccountnumber[i] != receiveraccount[i]){
			return 0;
		}
	}
	return 1;
}

int isSufficientBalance(char arr[7]) {
	long mBalance = 0, actB;
	for (int i = 0; i < 8; i++) {
		if (masterBalance[i] > '0') {
			return 1;
		}
	}
	for(int i = 0; i < 7; i++) {
		if (arr[i] < masterBalance[8 + i]) {
			return 1;
		} else if (arr[i] < masterBalance[8 + i]) {
			return 0;
		}
	}
	return 0;
}

void transferFund() {
	int flag1 = 0;
	char actAmt[7], amount[7];
	do {
		printf ("AMOUNT=>\n");
		scanf("%s", amount);
		if (amount[0] != '-') flag1= 1;
		else {
			printf ("INVALID AMOUNT\n");
		}
	} while (flag1 == 0);
	int size = 0;
	for (int i = 0; i < 7; i++) {
		if ((amount[i] >= '0' && amount[i] <= '9') || amount[i] == '.') {
			size++;
		} 
	}
	for (int i = size - 1, j = 6; i >= 0; i--) {
		if (amount[i] != '.') {
			actAmt[j] = amount[i];
			j--;
		}	
	}
	for(int i = 0; i < 7; i++) {
		if (actAmt[i] < '0' || actAmt[i] > '9') actAmt[i] = '0';
	}

	if (isSufficientBalance(actAmt) == 0) {
		printf("\nINSUFFIENT BALANCE\n");
		transferFund();
	}

	int ind = 0;
	for(int j = 0; j < 16; j++){
		toWrite[ind] = useraccount[j];
		ind++;
	}
	toWrite[ind] = 'W';
	ind++;
	for(int j = 0; j < 7; j++){
		toWrite[ind] = actAmt[j];
		ind++;
	}

	t++;
	char timeSt[5];
	int currT = t, k = 4;
	while(currT != 0 && k >=0){
		timeSt[k] = '0' + currT % 10;
		currT /= 10; 
		k--;
	}
	
	for(int j =0; j < 5; j++, ind++) {
		if (timeSt[j] <'0' || timeSt[j] > '9') {
			toWrite[ind] = '0';
		} else {
			toWrite[ind] = timeSt[j];
		}
	}
	toWrite[ind] = '\n';
	
	FILE *fp;
	if(atm == 1){
		fp = fopen("trans711.txt", "a+");
	}else{
		fp = fopen("trans713.txt", "a+");
	}
	fwrite(toWrite, 30, 1, fp);
	fclose(fp);

	for (int i = size - 1, j = 6; i >= 0; i--) {
		if (amount[i] != '.') {
			actAmt[j] = amount[i];
			j--;
		}	
	}
	for(int i = 0; i < 7; i++) {
		if (actAmt[i] < '0' || actAmt[i] > '9') actAmt[i] = '0';
	}

	int i = 0;
	for(int j = 0; j < 16; j++){
		toWrite[i] = receiveraccount[j];
		i++;
	}
	toWrite[i] = 'D';
	i++;
	for(int j = 0; j < 7; j++){
		toWrite[i] = actAmt[j];
		i++;
	}

	t++;
	char timeSt2[5];
	int currT2 = t, k2 = 4;
	while(currT2 != 0 && k2 >=0){
		timeSt2[k2] = '0' + currT2 % 10;
		currT2 /= 10; 
		k2--;
	}
	
	for(int j =0; j < 5; j++, i++) {
		if (timeSt2[j] <'0' || timeSt2[j] > '9') {
			toWrite[i] = '0';
		} else {
			toWrite[i] = timeSt2[j];
		}
	}
	toWrite[i] = '\n';
	
	FILE *fp2;
	if(atm == 1){
		fp2 = fopen("trans711.txt", "a+");
	}else{
		fp2 = fopen("trans713.txt", "a+");
	}
	fwrite(toWrite, 30, 1, fp2);
	fclose(fp2);
	continueFn();
}

void validateRAccount() {
	FILE * fp;
    int bufferLength=59;
    char buffer[bufferLength];

	if (isSameAccountForTransfer()) {
		printf("%s", receiveraccount);
		printf("\nYOU CANT TRANSFER TO YOUR OWN ACCOUNT\n");
		transfer();
		return;
	}

    fp=fopen("master.txt","r");
	int accountFound = 0;
    while((fgets(buffer, bufferLength, fp))!=NULL) 
    {
        buffer[strcspn(buffer, "\r\n")] = 0;
        int index=0,j=0, k=0, l=0, m=0;
        for(index=0; index<58;index++)
        {
            if (index<20){
            }
            else if (index<36){
                masteraccountnumber[k]=buffer[index];
                k++;
            }
            else {
            }
        } 
		accountFound = compareRAccountNumber();
        if (accountFound) {
			transferFund();
			break;
		}
    }
	if (accountFound == 0) {
		printf("%s", receiveraccount);
		printf(" INVALID ACCOUNT\n");
		transfer();
	}
    fclose(fp);
}

void transfer() {
	printf("\n TARGET ACCOUNT: \n");
	scanf("%s", receiveraccount);
	validateRAccount();
}
