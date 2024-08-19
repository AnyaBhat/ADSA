//Binary Counter
#include <stdio.h>

#define Max 1000

int main(){
    int n;
    char str[Max];
    printf("Enter the number of binary digits: ");
    scanf("%d",&n);
    printf("Enter the binary number:");
    scanf("%s",str);
    int i=n-1;
    while(i>=0 && str[i]=='1'){
        str[i] = '0';
        i--;
    }
     if (i >=0) {
        str[i] = '1'; // Set the first 0 bit to 1
    }else{
        printf("Result:");
        printf("1%s\n",str);
        return 0;
    }
    printf("Result:");
    printf("%s\n",str);
    return 0;

}
