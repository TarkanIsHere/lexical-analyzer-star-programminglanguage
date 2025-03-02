#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int contains(const char *str, const char *substr) {
    return strstr(str, substr) != NULL;
}
int containsoz(const char *str, char ch) {
    while (*str) {
        if (*str == ch) {
            return 1; // Karakter bulundu
        }
        str++;
    }
    return 0; // Karakter bulunamadı
}
// bir stringteki , sayısını bulan method.
int karakterSayisiniBul(char *string) {
    char karakter = ',';
    int sayac = 0;   
    for (int i = 0; string[i] != '\0'; ++i) {
        if (string[i] == karakter) {
            sayac++;
        }
    }
    return sayac;
}
// verilen bir stringteki .'yı kaldıran method.
char* noktayiKaldir(char *str) {
    int uzunluk = strlen(str);
    char* yeniKelime = (char*)malloc((uzunluk + 1) * sizeof(char));
    
    strcpy(yeniKelime, str); // Orjinal stringi yeni stringe kopyala

    if (uzunluk > 0 && yeniKelime[uzunluk - 1] == '.') {
        yeniKelime[uzunluk - 1] = '\0'; // Son karakteri sil
    }
    return yeniKelime;
}

int main(){
    // Kodta kullanılmak üzere tanımlanan özel değişkenler ve arrayler.
    char keywords[8][10] = {"int", "text", "is", "loop", "times", "read", "write", "newLine"};
    char alfabe[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    char *operators[] = {"+","-","*","/"};
    char digits[10][25] = {"0", "1", "2", "3","4","5","6","7","8","9"};
    char *digitss[] = {"0", "1", "2", "3","4","5","6","7","8","9"};
    char *endofline  = ".";
    char *comma = ",";
    char *leftcurlybracket = "{";
    char *rightcurlybracket = "}";

    // Dosya açma ve Okuma İşlemleri
    char *readfilename = "code.sta.txt";
    FILE *fp = fopen(readfilename, "r");

    char *writefilename = "code.lex.txt";
    FILE *file = fopen(writefilename, "w");

    if (fp == NULL)
    {
        printf("Error: Dosya Bulunamadi %s", readfilename);
        return 1;
    }
    // control statementlerı için özel değişkenler.
    char ch;
    char kelime[100];
    char kelime1[200];
    char *belirsiz;
    char *string1;
    int comment = 0;
    int integerControl = 0;
    int keywordCheck = 0;
    int stringCheck = 0;
    char str1[256] = "";  
    int stringUzunluk = 0;
    int identifierCheck = 1;
    int integerCheck = 1;
    int operatorCheck = 0;
    int commaCheck = 0;  
    int identifierLongCheck = 0;
    int identifierApproriate = 0;
    int negativeIntegerCheck = 0;
    int maxIntegerSizeCheck = 0;
    // txt dosyasının  kelime kelime okunması.
    while (fscanf(fp, "%s", kelime) != EOF) {
        printf("%s\n", kelime);
        char *integ = "";
        int kelimeUzunluk = strlen(kelime);
        // Comment'in olup olmadığını kontrol etmek
        if(contains(kelime,"/*")){
            comment = 1;
        }
        // Comment yoksa aşağıdaki if bloğunu çalıştır.
        if(comment == 0){
            for(int i = 0; i <= 7; i++){
                if(contains(kelime, keywords[i])){
                    fprintf(file, "Keyword(%s)\n", keywords[i]);
                    keywordCheck = 1;
                }
            }
            // operator kontrolü
            for(int i = 0; i <=3; i++){
                if(kelime[0] != '-'){
                    if(contains(kelime, operators[i])){
                    operatorCheck = 1;
                    }
                }
                
            }    
            // string kontrolü " =  34  
            if(kelime[0] == 34){
                stringCheck = 1;                     
            }
            // eğer okunan kelimede operator varsa aşağıdaki if bloğuna gir.
            if(operatorCheck){
                int sayac = 0;
                char *operator;
                for(int i = 0; i<4; i++){
                    if(contains(kelime, operators[i])){
                        operator = operators[i];
                    }
                }
                char *kelime_kopyasi = strdup(kelime);
                char *parca = strtok(kelime_kopyasi, operator);
                // operator olan kelime parçasını tek tek ayırmak.
                while (parca != NULL) {
                    // printf("Buradaki parca: %s\n",parca);
                    for(int i = 0; i < 52; i++){
                            if(containsoz(noktayiKaldir(parca), alfabe[i])){
                                integerCheck = 0;
                            }
                    }
                    // eğer ayrılan kelime integersa buraya gir ve gerekli hata kontrollerini yap.
                    if(integerCheck){
                        maxIntegerSizeCheck = strlen(parca);
                        if(maxIntegerSizeCheck > 8){
                            fprintf(file, "Integer Error: Maximum integer Size Must be 8 Digits\n");
                            return 1;
                        }else{
                            // printf("buradaki karakter integer: %s", parca);
                        if(parca[0] == '-'){
                            sayac +=1;
                            if(sayac == 2){
                            fprintf(file, "Operator(%s)\n", operator);
                        }
                            // Integers must be a positive value.
                            fprintf(file, "IntConst(%s)\n", "0");
                            parca = strtok(NULL, operator);
                           
                        }else{  
                            sayac +=1;
                        if(sayac == 2){
                            fprintf(file, "Operator(%s)\n", operator);
                        }
                        fprintf(file, "IntConst(%s)\n", noktayiKaldir(parca));
                        parca = strtok(NULL, operator);
                            
                        }
                        }
                        // else'e girerek identifier kontrolünü yapmak.    
                    }else{
                        for(int i = 0; i < 52; i++){
                            if(parca[0] == alfabe[i]){
                                identifierApproriate = 1;
                            }
                        }
                        if(identifierApproriate){
                            identifierLongCheck = strlen(parca);
                            if(identifierLongCheck > 8){
                                fprintf(file, "Identifier Error: Max Long Error");
                                return 1;
                        }else{
                            sayac +=1;
                            if(sayac == 2){
                                fprintf(file, "Operator(%s)\n", operator);
                            }
                            fprintf(file, "Identifier(%s)\n", noktayiKaldir(parca));
                            parca = strtok(NULL, operator);
                            }
                        }else{
                            fprintf(file, "Identifier Error: Wrong Identifier Name, Identifier Must Start With Alphabetic.");
                            printf("Uygunsuz Identifier Kullanimi");
                            return 1;
                        }                        
                    }
                    integerCheck = 1;
                    identifierApproriate = 0;
                    maxIntegerSizeCheck = 0;
                }  
            }else{
                // operator olmadığında yukarıdaki işlemleri operatorsüz bir biçimde yapmak.
                if(stringCheck == 0){
                if(keywordCheck == 0){
                    
                     for(int i = 0; i < 52; i++){
                            if(containsoz(kelime, alfabe[i])){
                                integerCheck = 0;
                            }
                        }
                    if(integerCheck){
                        maxIntegerSizeCheck = strlen(kelime);
                        if(maxIntegerSizeCheck > 8){
                            fprintf(file, "Integer Error:Maximum integer Size Must be 8 Digits\n");
                            return 1;
                        }else{
                            // printf("buradaki karakter integer: %s", kelime);
                        if(kelime[0] == '-' ){
                            // Integers must be a positive.
                            fprintf(file, "IntConst(%s)\n", "0");
                        }else{
                            
                            if(kelime[0] != '{'){
                                if (kelime[0] != '}')
                                {
                                    fprintf(file, "IntConst(%s)\n", noktayiKaldir(kelime));
                                }
                            }
                        // bracket kontrolünü yapmak.
                        if(strcmp(kelime, rightcurlybracket) == 1){
                            fprintf(file, "RightCurlyBracket()\n");
                        }
                        } 
                        }                            
                    }else{
                        char *kelime_kopyasi = strdup(kelime);
                        char *parca = strtok(kelime_kopyasi, ",");
                        int sayacComma = 0;
                        int commaKoy = 0;
                        sayacComma = karakterSayisiniBul(kelime);
                        // printf("Burada %d", sayacComma);
                        while (parca != NULL) {
                            if(parca[0] != 34){
                                for(int i = 0; i < 52; i++){
                            if(parca[0] == alfabe[i]){
                                identifierApproriate = 1;
                            }
                        }
                        if(identifierApproriate){
                            identifierLongCheck = strlen(parca);
                            if(identifierLongCheck > 8){
                                fprintf(file, "Identifier Error: Max Long Error\n");
                                return 1;
                            }else{
                                commaKoy += 1;
                                fprintf(file, "Identifier(%s)\n", noktayiKaldir(parca));
                                if(commaKoy != 0 && sayacComma > 0 ){
                                    fprintf(file, "Comma()\n");
                                } 
                                sayacComma -=1;
                                parca = strtok(NULL, ",");
                            }
                        }else{
                            fprintf(file, "Identifier Error: Wrong Identifier Name, Identifier Must Start With Alphabetic.");
                            printf("Uygunsuz Identifier Kullanimi");
                            return 1;
                            identifierApproriate = 0;   
                            }
                        }
                        }
                        
                    }

                }
            }else{
                // string durumları
                if(stringCheck){
                stringUzunluk += kelimeUzunluk;
                strcat(kelime, " ");
                strcat(str1, kelime);
            }
            if(kelime[kelimeUzunluk - 1] == 34){
                stringCheck = 0;
                fprintf(file, "String(%s)\n", str1);
                memset(str1, 0, sizeof(str1));
            }
            if(kelime[kelimeUzunluk - 2] == 34){
                stringCheck = 0;
                fprintf(file, "String(%s)\n", str1);
                memset(str1, 0, sizeof(str1));
            }
            }
            }
            // bracket kontrolü
            if(strcmp(kelime, leftcurlybracket) == 0){
                fprintf(file, "LeftCurlyBracket()\n");
            }
            if(strcmp(kelime, rightcurlybracket) == 0){
                fprintf(file, "RightCurlyBracket()\n");
            }
            // enf of line kontrolü
            if(contains(kelime, endofline)){
                fprintf(file, "EnfOfLine\n");
            }
        }
        if(contains(kelime, "*/")){
            comment = 0;
            integerControl = 0;
        }

        if(stringUzunluk > 256){
            printf("String Çok Uzun");
            fprintf(file, "String Error:Max Length Must Be 256 Character\n");
            return 1;
        }
        // değişkenlerin while'dan çıkarken tekrar ayarlanması
        identifierCheck = 1;
        integerCheck = 1;
        keywordCheck = 0;
        operatorCheck = 0;
        commaCheck = 0;
        identifierLongCheck = 0;
        identifierApproriate = 0;
        maxIntegerSizeCheck = 0;
    }
    // Comment Açılıp Kapatılmadıysa Hata
    if(comment){
        printf("Hatali Comment Kullanimi");
        fprintf(file, "Error Found: Comment Error\n");
    }
    // String açılıp kapanmadıysa Hata
    if(stringCheck){
        printf("Hatali String Kullanimi");
        fprintf(file, "Error Found: String Error, Something is missing \n");
    }
    return 0;

}
