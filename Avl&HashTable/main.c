#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <stdbool.h>
#define MAX 250

typedef long long ll ; // redefine


typedef struct word_node {

    char word[30];
    char meaning[MAX];
    char synonym[30];
    char antonym[30];

} *Word ;

typedef struct tree {

    Word node ;
    struct tree * Left;
    struct tree * Right;
    int Hight;
} *Tree ;

typedef struct hash {// Hash Table Contain the city and two boolean to remark the sells

    Word node  ;
    bool del ; // remark the cell deleted
    bool vis ; // remark the cell visited


} Hash;

Tree MakeEmpty( Tree T ){

    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

int Hight( Tree h ){
    if( h == NULL )
        return -1;
    else
        return h->Hight;
}

int Max( int Lhs, int Rhs ){
    return Lhs > Rhs ? Lhs : Rhs;
}

Tree SingleRotateWithLeft( Tree K2 ){
    Tree K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Hight = Max( Hight( K2->Left ), Hight( K2->Right ) ) + 1;
    K1->Hight = Max( Hight( K1->Left ), K2->Hight ) + 1;

    return K1;  /* New root */
}

Tree SingleRotateWithRight( Tree K1 ){
    Tree K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Hight = Max( Hight( K1->Left ), Hight( K1->Right ) ) + 1;
    K2->Hight = Max( Hight( K2->Right ), K1->Hight ) + 1;

    return K2;  /* New root */
}

Tree DoubleRotateWithLeft( Tree K3 ){
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}

Tree DoubleRotateWithRight( Tree K1 ){
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}


int Find_Size(Tree T){

  if (T==NULL)
    return 0;
  else
    return(Find_Size(T->Left) + 1 + Find_Size(T->Right));
}

Tree Find_Max(Tree T ){
    if(T == NULL )
        return NULL ;
    if(T->Right == NULL)
        return T ;
    else
    {
        return Find_Max(T->Right) ;

    }
}

int B_F(Tree root){
    int c =0, c1 =0 ;
    if(root->Left != NULL)
        c = root->Left->Hight+1 ;
    if(root->Right != NULL )
        c1 = root->Right->Hight+1 ;
    return c - c1 ;
}

int update_higth(Tree root ){
    int c =-1, c1 =-1 ;
    if(root->Left != NULL)
        c = root->Left->Hight ;
    if(root->Right != NULL )
        c1 = root->Right->Hight ;
    return c >= c1 ? c+1 : c1+1 ;
}
Tree LL( Tree root ){

    Tree temp ;
    temp = root->Left ;
    root->Left = temp->Right ;
    temp->Right = root ;
    root->Hight = update_higth(root) ;
    temp->Hight = update_higth(temp ) ;

    return temp ;
}

Tree RR( Tree root ){

    Tree temp = root->Right;
    root->Right = temp->Left ;
    temp->Left = root ;
    root->Hight = update_higth(root);
    temp->Hight = update_higth(temp);
    return temp ;
}

Tree balance(Tree root ){

    if(root == NULL )
        return NULL ;
    else{

        if(B_F(root) == 2){

            if(B_F(root->Left) == -1) // Left Right case
                root->Left = RR(root->Left);
            root = LL(root) ;
        }
        else if(B_F(root ) == -2 ){
            if(B_F(root->Right) == 1 ) // Right Left case
                root->Right = LL(root->Right);
            root = RR(root) ;
        }

        root->Hight = update_higth(root) ; // update the hight
        return root ;
    }
}


Tree NewNode(Word node){            // get node of a new word

    Tree t = (Tree)malloc(sizeof(struct tree)) ;
    t->Hight = 0 ;
    t->node = node;
    t->Left = t->Right = NULL ;
    return t ;



}

Word New_Word(char word[30],char meaning[MAX],char synonym[30],char antonym[30]){       // insert new word

    Word w = (Word) malloc(sizeof(struct word_node)) ;
    strcpy(w->word,word) ;
    strcpy(w->meaning,meaning) ;
    strcpy(w->synonym,synonym) ;
    strcpy(w->antonym,antonym);
    return w ;
}

Tree InsertNode( Tree root , Word node ){


    if( root == NULL ){

        Tree temp = NewNode(node);
        return temp ;
    }

    else{

    /*Binary search tree bases with balance small than root to the left larger than root to the right */
        if( strcmp(root->node->word , node->word) > 0 ){
        root->Left = InsertNode(root->Left,node);

        }
        else if( strcmp(root->node->word,node->word) < 0 ){
            root->Right = InsertNode(root->Right,node);

        }

        root->Hight = update_higth(root) ;
        root = balance(root) ;
        return root ;
    }





}

Tree readWordInformation(Tree T){


    char word[30],meaning[MAX],synonym[30],antonym[30];//define parameters
    FILE*file;
    file=fopen("Words.txt","r");
    char tempVariableData [300];//temporary variable contain the data from shares file
    while(fgets(tempVariableData,250,file)!=NULL)// Keep iterate till the end of the file
    {
        strcpy(word,strtok(tempVariableData,":"));
        strcpy(meaning,strtok(NULL,"/"));
        strcpy(synonym,strtok(NULL,"*"));
        strcpy(antonym,strtok(NULL,"*"));

        Word x = New_Word(word,meaning,synonym,antonym);


        T = InsertNode(T,x);









    }

    return T;
}

void List(Tree T  ){
    if( T != NULL)
    {
        List( T->Left );
        printf("%Word : %s\tMeaning: %s\tSynonym: %s\t Antonym: %s\n", T->node->word,T->node->meaning,T->node->synonym,T->node->antonym);
        List( T->Right );
    }
}

Tree Word_Search(char w[30],Tree T){

    if( T == NULL )
        return NULL ;

    else{

       if( strcmp(w,T->node->word) < 0 ){
           return Word_Search( w, T->Left );
       }
        else if( strcmp(w,T->node->word) > 0 ){
            return Word_Search( w, T->Right );
        }
    else
        return T ;


    }

}

Tree Letter_Search(Tree T , char l[2]){



    if( T == NULL )
        return NULL ;

    else{

       if( strncmp(l,T->node->word,1) < 0 ){
           return Letter_Search(T->Left , l );
       }
        else if( strncmp(l,T->node->word , 1) > 0 ){
            return Letter_Search( T->Right , l  );
        }
    else
        return T ;


    }

}

Tree Find_Node(Tree T){

    char sWord [30];
    char update[2] ;
    Tree result;
    printf("\n\t\tEnter The Word : ");
    gets(sWord);
    result = Word_Search(sWord,T);
    if(result==NULL)
        printf("\n\t\tSorry .. no word founded !!\n");
    else{
        printf("\n\t\tThe Specific word is Founded !!\n");
        printf("\n\t\tThe Word is : %s", result->node->word );
        printf("\n\t\tThe Meaning is : %s", result->node->meaning );
        printf("\n\t\tThe Synonym is : %s", result->node->synonym );
        printf("\n\t\tThe Antonym is : %s", result->node->antonym );
        printf("\n\n\t\tPress 1 to update the information of the word OR 0 to close >> ");
        gets(update);
        if(strcmp(update,"1")==0){
            char meaning[MAX] , synonym[30],antonym[30] , meaning2[80] ,  meaning3[80] , nom[2];
            printf("\n\t\tThe Word is : %s\n", result->node->word );
            do{
                printf("\n\t\tHow many meaning Do you want to put [ up to 3 ] >> ");
                gets(nom);
                if(nom[0]>='1' && nom[0]<='3' && strlen(nom) == 1){     // choice user number of meaning he want to store
                    switch(nom[0]){
                        case '1' :

                             printf("\n\t\tWrite the Meaning  : ");
                             gets(meaning) ;

                        break ;
                        case '2' :

                            printf("\n\t\tWrite the first Meaning   : ");
                            gets(meaning) ;
                            appendchar(meaning,',');
                            printf("\n\t\tWrite the second Meaning   : ");
                            gets(meaning2) ;
                            strcat(meaning,meaning2);
                        break ;
                        case '3' :
                            printf("\n\t\tWrite the first Meaning   : ");
                            gets(meaning) ;
                            appendchar(meaning,',');
                            printf("\n\t\tWrite the second Meaning   : ");
                            gets(meaning2) ;
                            strcat(meaning,meaning2);
                            appendchar(meaning,',');
                            printf("\n\t\tWrite the third Meaning   : ");
                            gets(meaning3);
                            strcat(meaning,meaning3);
                        break ;

                    }
                }
                else{
                    clear_screan() ;
                    printf("\n\t\tThe number isn't in list try again.\n");
                }
            }while(nom[0] !='1' && nom[0]!='2' && nom[0] !='3' );

            strcpy(result->node->meaning,meaning);
            printf("\n\t\tWrite the Synonym : ");
            strcpy(result->node->synonym,gets(synonym));
            printf("\n\t\tWrite the Antonym : ");
            strcpy(result->node->antonym,gets(antonym));
            printf("\n\t\tThe information of the word is updating successfully !! ");

        }
        else
          return;
    }

}

void List_Syn_Ant(Tree T){

    char sWord [30];
    Tree result;
    printf("\n\t\tEnter The Word : ");
    gets(sWord);
    result = Word_Search(sWord,T);
    if(result==NULL)
       printf("\n\t\tSorry .. no word founded !!\n");
    else{

        printf("\n\t\tThe synonym of the Word is : %s\n", result->node->synonym );
        printf("\n\t\tThe antonym of the Word is : %s\n", result->node->antonym );
    }

    return;

}

void List_First_Letter(char l[2],Tree T){

     if( T != NULL){

        List_First_Letter(l , T->Left );
        if(l[0]==T->node->word[0]){
            printf("\n\t\tThe Word is : %s\n",T->node->word);
        }

        List_First_Letter(l, T->Right );
    }

}

Tree Delete_Node(Tree T , Word w){


    if(T == NULL )
        return NULL ;
    else
    {
        if( strcmp(T->node->word, w->word) > 0 )
        {
            T->Left = Delete_Node(T->Left, w);
        }
        else if( strcmp(T->node->word, w->word ) < 0 )
        {
            T->Right = Delete_Node(T->Right, w ) ;
        }
        else
        {
            if(T->Left != NULL && T->Right != NULL) // if two child exist
            {
                Tree temp = Find_Max(T->Left);
                T->node = temp->node ;
                T->Left = Delete_Node(T->Left, temp->node);
                return T ;
            }
            else // if one child
            {
                Tree temp = NULL ;
                if(T->Left != NULL)
                    temp = T->Left ;
                if(T->Right != NULL)
                    temp = T->Right ;
                free(T) ;
                return temp ;
            }

        }
        T = balance(T) ; // balancing
        T->Hight = update_higth(T) ; // update hight

        return T ;
    }
}

void Delete_As_Word(Tree T ){

    char sWord [30];
    char c[2] ;

    printf("\n\t\tEnter The Word you want to delete it : ");
    gets(sWord);
    Word result = New_Word(sWord,"","","");
    Tree tt = Word_Search(result->word,T);

    if(tt==NULL)
        printf("\n\t\tSorry no word founded !! \n");
    else{
        T = Delete_Node(T,result);
        printf("\n\t\tThe word is Deletion successfully !!\n\n");

    }



}

void Delete_As_Letter(Tree T ){


    char sLetter [2];
    int x = 2 ;

    printf("\n\t\tEnter The Letter you want to delete it : ");
    gets(sLetter);
    Word result = New_Word(sLetter,"","","");

    Tree tt = Letter_Search(T , sLetter);
    Tree ttt = Letter_Search(T , sLetter);

    if(tt==NULL)
        printf("\n\t\tSorry no word founded !! \n");
    else{
            while(tt!=NULL){
                T = Delete_Node(T,tt->node);
                tt = Letter_Search(T , sLetter);
            }

            printf("\n\t\tThe words is Deletion successfully !!\n\n");
            return T;



    }


}

void appendchar(char* s, char c) {    // add char to the string
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

void saveInFile( Tree  T ,FILE*in){
    if( T != NULL)
    {
        saveInFile( T->Left,in );
        fprintf(in,"%s : %s / %s * %s", T->node->word , T->node->meaning , T->node->meaning , T->node->antonym);
        saveInFile( T->Right,in );
    }
}

void clear_screan() // clear screen
{
    system("cls");
    printf("\n\t\t_______________________________________________________________________________\n\n");

}

void end_screan(int b)  // wait the user
{
    char g[256];
    printf("\n\n\n\t\t Press Enter to back to the menu ... ");
    if(b)
        gets(g);
    gets(g);
    system("cls");
    printf("\n\t\t_______________________________________________________________________________\n\n");

}


// ---------Function of Hash Table ---------

int get_prime(int x);
Hash * insert_hash( Word  c , int n, Hash* h );
Hash* create_table(int size);
int get_prime(int x);
int get_key( char *c, int size );
Hash * rehash_table(Hash *table, int n );
Hash * insert_hash( Word c , int wsize , Hash* h );
Hash * Delete_Value( Hash * t, int size , char* c );
int Search_Value(Hash *t, int size ,char* c, int flag);
int get_size(Hash* h, int size );
void print_table(Hash *h,int size);
void print_hash_file(Hash *h, int size );
void print_hash(Hash  *t, int size );
Hash *implement_table( Tree root , int avlsize);





void Menu_Hash(Hash * table, int size);

int main(){            // start the program

    Tree T;
    FILE * out  ;
    T = MakeEmpty(NULL);
    char word[30] , meaning[MAX] , synonym[30],antonym[30] , meaning2[80] ,  meaning3[80]  ;   // to store the data
    char nom[2];

    char choice[3];
    do
    {
        //show Menu on the screen
        printf("\n\t\t__________________________Project 3 - Data Structure_______________________________\n") ;
        printf("\t\t____________________________Mohammad Qashoo 1183336_______________________________\n") ;
        printf("\n\n\t\t\t Choose one of the following : \n\n") ;
        printf("\t\t\t 1) Read the Data [ Words.txt ] \n\n") ;
        printf("\t\t\t 2) Insert a new Word\n\n") ;
        printf("\t\t\t 3) Search for a specific Word\n\n") ;
        printf("\t\t\t 4) Print all Word \n\n") ;
        printf("\t\t\t 5) Print the synonym and antonyms of a given word\n\n") ;
        printf("\t\t\t 6) Print all words that start of a given letter\n\n") ;
        printf("\t\t\t 7) Delete a specific Word\n\n") ;
        printf("\t\t\t 8) Delete all words that start of a given letter\n\n") ;
        printf("\t\t\t 9) Save all words in the file [ Dictionary.txt ]\n\n") ;
        printf("\t\t\t >>> Press [ h ] to Implement the Hash Table\n\n") ;
        printf("\t\t\t >>> Press [ e ] to EXITS.\n\n\t\t\t ->") ;

        gets(choice);//get choice number from the user

        switch(choice[0]){    //shows cases depending on the choice value
        case '1':

          clear_screan();
          T = readWordInformation(T);                   // read the data
          printf("\n\t\tThe file has been reading successfully !! \n");
          end_screan(0);

        break;
         case '2':                     // insert new data

            clear_screan();
            printf("\n\t\t Write the word : ");
            gets(word) ;
            printf("\n\t\t______________________________\n");


            do{
                     printf("\n\t\tHow many meaning Do you want to put [ up to 3 ] >> ");
                    gets(nom);
                     if(nom[0]>='1' && nom[0]<='3' && strlen(nom) == 1){   // choice user number of meaning he want to store
                            switch(nom[0]){
                                case '1' :

                             printf("\n\t\t Write the Meaning  : ");
                             gets(meaning) ;

                                break ;
                                case '2' :

                            printf("\n\t\t Write the first Meaning   : ");
                            gets(meaning) ;
                            appendchar(meaning,',');
                            printf("\n\t\t Write the second Meaning   : ");
                            gets(meaning2) ;
                            strcat(meaning,meaning2);


                                break ;
                                case '3' :
                            printf("\n\t\t Write the first Meaning   : ");
                            gets(meaning) ;
                            appendchar(meaning,',');
                            printf("\n\t\t Write the second Meaning   : ");
                            gets(meaning2) ;
                            strcat(meaning,meaning2);
                            appendchar(meaning,',');
                            printf("\n\t\t Write the third Meaning   : ");
                            gets(meaning3);
                            strcat(meaning,meaning3);
                                break ;

                            }
            }
            else{
                clear_screan() ;
                printf("\n\t\tThe number isn't in list try again.\n");
            }

            }while(nom[0] !='1' && nom[0]!='2' && nom[0] !='3' );

            printf("\n\t\t______________________________\n");
            printf("\n\t\t Write the Synonym  : ");
            gets(synonym) ;
            printf("\n\t\t______________________________\n");
            printf("\n\t\t Write the Antonym : ");
            gets(antonym) ;
            Word x = New_Word(word,meaning,synonym,antonym);
            T = InsertNode(T,x);
            printf("\n\n\t\tThe Word have been inserted successfully \n\n");
            end_screan(0);

        break;

        case '3':
            clear_screan();
            Find_Node(T);         // search & update
            end_screan(0);
        break;

        case '4':
            clear_screan();
            List(T);         // print the tree
            end_screan(0);

        break;
        case '5':
            clear_screan();
            List_Syn_Ant(T);
            end_screan(0);

        break;
         case '6':               // Search according letter
            clear_screan();
            char sLetter [2];
            printf("\n\t\tEnter the Letter : ");
            gets(sLetter);
            Tree temp;
            temp=Letter_Search(T,sLetter);
            if(temp!=NULL){
                List_First_Letter(sLetter,T);

            }
            else{
                     printf("\n\t\tSorry ... no word founded !!");

            }

            end_screan(0);

        break;
         case '7':            // delete according word
              clear_screan();
             Delete_As_Word(T);
             end_screan(0);

        break;
        case '8':                   // delete according letter
              clear_screan();
            Delete_As_Letter(T);
             end_screan(0);
        break;

        case '9' :               // save tree in file
            clear_screan();
            out = fopen("Dictionary.txt","w");
            saveInFile(T,out);
            fclose(out);
            printf("\n\t\tThe operation is completed successfully\n");
            end_screan(0);
        break;


        case 'h' :
            clear_screan();
            int avlsize = Find_Size(T);
            Hash* h = implement_table(T , avlsize) ;
            menu_hash(h, avlsize );
            clear_screan();

        break;
    }

} while(choice[0] != 'e');



    return 0;
}


void menu_hash(Hash * table, int size) // menu of hash
{
    int numOfelement = size ;      // capacity 0f the hash table
    int n = get_prime(size*2+1) ; // get the prime after 2*n
    char line[256] ;
    do
    {
         // menu of the hash table
        printf("\n\n\t\t\t Choose one of the following.\n\n") ;
        printf("\t\t\t 1) Print HashTable\n\n") ;
        printf("\t\t\t 2) Print Table Size\n\n") ;
        printf("\t\t\t 3) Print Use HashFunction.\n\n") ;
        printf("\t\t\t 4) Insert a new Word\n\n") ;
        printf("\t\t\t 5) Search for a specific Word.\n\n") ;
        printf("\t\t\t 6) Delete a specific Word\n\n") ;
        printf("\t\t\t 7) Save Hash Table to file\n\n") ;
        printf("\t\t\t 8) Back to menu\n\n") ;
        printf("\t\t\t 9) EXITS\n\n\t\t\t ->") ;
        gets(line) ;
        if(strlen(line)>=2 && line[0]>'9' && line[0]<='0')
            continue;

        switch(line[0])
        {
        case '1' :
            clear_screan();
            print_table(table,n);
            end_screan(0);
            break ;
        case '2' :
            clear_screan() ; // print the size of table
             printf("\n\n\t\tThe size of Table : %d \n\n\t\tThe Number Of element : %d\n",n, numOfelement) ;

            end_screan(0) ;
            break ;
        case '3' :
            clear_screan() ; // insert new record

            print_hash(table, n); // print hash function

            end_screan(0);
            break ;
        case '4' :

            clear_screan();
            char hword[30] , hmeaning[MAX] , hsynonym[30],hantonym[30] , hmeaning2[80] ,  hmeaning3[80]  ;
            char hnom[2];

             printf("\n\t\t Write the word : ");
            gets(hword) ;
            printf("\n\t\t______________________________\n");


            do{
                     printf("\n\t\tHow many meaning Do you want to put [ up to 3 ] >> ");
                    gets(hnom);
                     if(hnom[0]>='1' && hnom[0]<='3' && strlen(hnom) == 1){   // choice user number of meaning he want to store
                            switch(hnom[0]){
                                case '1' :

                             printf("\n\t\t Write the Meaning  : ");
                             gets(hmeaning) ;

                                break ;
                                case '2' :

                            printf("\n\t\t Write the first Meaning   : ");
                            gets(hmeaning) ;
                            appendchar(hmeaning,',');
                            printf("\n\t\t Write the second Meaning   : ");
                            gets(hmeaning2) ;
                            strcat(hmeaning,hmeaning2);


                                break ;
                                case '3' :
                            printf("\n\t\t Write the first Meaning   : ");
                            gets(hmeaning) ;
                            appendchar(hmeaning,',');
                            printf("\n\t\t Write the second Meaning   : ");
                            gets(hmeaning2) ;
                            strcat(hmeaning,hmeaning2);
                            appendchar(hmeaning,',');
                            printf("\n\t\t Write the third Meaning   : ");
                            gets(hmeaning3);
                            strcat(hmeaning,hmeaning3);
                                break ;

                            }
            }
            else{
                clear_screan() ;
                printf("\n\t\tThe number isn't in list try again.\n");
            }

            }while(hnom[0] !='1' && hnom[0]!='2' && hnom[0] !='3' );

            printf("\n\t\t______________________________\n");
            printf("\n\t\t Write the Synonym  : ");
            gets(hsynonym) ;
            printf("\n\t\t______________________________\n");
            printf("\n\t\t Write the Antonym : ");
            gets(hantonym) ;
            Word hw = New_Word(hword,hmeaning,hsynonym,hantonym);  // crate a new word
            table = insert_hash(hw, size ,table) ;                  // insert to the hash table
            if(numOfelement == size)
            {
                size = n ;
                n = get_prime(n*2+1);
            }
            numOfelement++ ;
            printf("\n\t\tThe Word has been inserted !! ");

            end_screan(0);
            break ;
        case '5' :
            clear_screan() ;
            char sword[30];
            printf("\tEnter the Word : ");
            gets(sword);
            if(!Search_Value(table, n, sword, 0) )
            {
                printf("\n\tNo Words Found");
            }
            end_screan(0);
            break ;
        case '6' :             // Delete the word
            clear_screan() ;

            char dword[30];
            printf("\n\n\tEnter the Word You Want to delete it : ");

            gets(dword);
            if(!Search_Value(table, n, dword, 0) )
            {
                printf("\n\n\tNo Words Founded !! ");
            }
            else{
                char cc[2] ;
                printf("\n\t\tAre you sure that you want to delete the previous word !!\n");
                printf("\n\t\tIf yes Press [ 1 ] , to cancel press [ 0 ]>>");
                gets(cc);
                if(strcmp(cc,"1")==0){
                table=Delete_Value(table,n,dword);
                numOfelement--;
                printf("\n\t\tThe words is Deletion successfully !!\n\n");
                }
                else
                end_screan(0);
            }
            end_screan(0) ;
            break ;
        case '7' :
            clear_screan() ;

         print_hash_file(table, n); // print in  the file
         printf("\n\t\tDone" );

             end_screan(0);
            break ;
        case '8' : // back to the menu
           break;
        case '9' :
            exit(1); // exit
            break ;
        }

    }
    while(line[0] != '8');

}




Hash* create_table(int size){ // create new hash table
    int x = get_prime(size*2+1) , i=0; // get the print after 2*n

    Hash* table = ( Hash* )malloc(sizeof(struct hash)*x) ; // create the table
    for(i=0; i<x ; i++ )
    {
        table[i].node = NULL ;
        table[i].vis = 0 ;


    }
    return table ;
}
int get_prime(int x){ // get the prime number after x

    int i = 3, temp = 1 ;
    for( ; x<1e9 ; x+=2 )
    {
        for(i=3 ; i*i<=x ; i+=2)
        {
            if(x%i == 0) // if is not prime
            {
                temp =0 ;
                break ;
            }
        }
        if(temp)
            return x ;
        temp =1 ;
    }
    return x ;
}

int get_key( char *c, int size ){ // hash function

    long long hv = 1, i =0;
    for(i=0 ; i<strlen(c) ; i++){
        hv = ( ( (hv<<2) + ( (long long)c[i]-60) ) ) ; // equation of hash
        }

    return ((hv%size)+size)%size ; // resize the
}

Hash * rehash_table(Hash *table, int n ){ // rehash

    Hash  *new_table = create_table(n) ;
    int i =0 ;
    for(i = 0 ; i<n ; i++)
    {
        if(table[i].vis  && table[i].node != NULL)
        {
            insert_hash(table[i].node, n, new_table) ;

        }
    }
    return new_table ;
}



Hash * insert_hash( Word c , int wsize , Hash* h ){

    int tsize = get_prime(2*wsize+1) ; // get the prime

    int key = get_key( c->word, tsize ) , ind = key ; // get the key of hash
    if(get_size(h, tsize) < wsize  ) // check if hash or rehash
    {
        int i = 0 ;
        while( h[ind].vis  ) // quadratic hash
        {
            i++;
           ind = (key+i*i)%tsize;
        }
        h[ind].node = c;
        h[ind].vis = 1 ; // remark the vis

    }
     else
    {
        h = rehash_table(h, tsize) ; // rehash table size
        wsize = tsize ;
        tsize = get_prime(tsize*2+1 ) ; // get prime
        h = insert_hash( c, wsize , h); // insert the element to hash table
    }

    return h;
}


Hash * Delete_Value( Hash * t, int size , char* c ){ // delete word

    int key = get_key( c , size ) ; // find the key
    int i = 0 , ind = key ;
    while( (strcmp(t[ind].node->word,c) != 0 && t[ind].vis)   )
    {
        i++ ;
        ind = (key+i*i)%size ; // quadratic hash
    }
    t[ind].node = NULL;// remark it deleted
    t[ind].vis = 0 ;
    return t ;
}






int Search_Value(Hash *t, int size ,char* c, int flag){ // search about the word

    int st =1 ;
    int key = get_key(c, size ) ;
    int i =0 ,ind = key ;

    while( t[ind].vis ) // if vis
    {
        if(  strcmp(t[ind].node->word ,c) == 0 ) // if not the word
        {
            if(flag)
                return 1;
            st = 0 ;
            printf("\n\tThe index is %d | Word : %s | Meaning : %s | Synonym : %s | Antonym : %s\n", ind ,t[ind].node->word , t[ind].node->meaning , t[ind].node->synonym , t[ind].node->antonym);
        }
        i++ ;
        ind = (key + i*i)%size; // quadratic hash
    }
    if(st)
        return 0 ;
    else
        return 1 ;
}


int get_size(Hash* h, int size ){ // get size of table

    int i =0, n =0 ;
    for(i =0 ; i<size ; i++)
    {
        if(h[i].vis == 1) // if visited count them
            n++;
    }
    return n ;
}

void print_table(Hash *h,int size){ // print the table

    int i =0 ;
    for(i =0 ; i < size ; i++)
    {
        if(h[i].vis){

         // if the cell contain values

            printf("\n\t\t>>>The index %d | Word : %s | Meaning : %s | Synonym : %s | Antonym : %s | vis -> %d", i ,h[i].node->word , h[i].node->meaning , h[i].node->synonym , h[i].node->antonym , h[i].vis);
            printf("\n\t\t___________________________________________________________________________________________\n");
        }
        else
        {
            printf("\n\t\t>>>The index %d | (empty) | vis -> %d    \n",i, h[i].vis );
             printf("\n\t\t___________________________________________________________________________________________\n");

        }
    }
}


void print_hash_file(Hash *h, int size ){ // print the hash in the file

    FILE * fp;
   int i;

   fp = fopen ("Dictionary.txt","w");        // open the file for writing


   for(i = 0 ; i < size ; i++){
        if (h[i].vis)
       fprintf (fp, "%s : %s / %s * %s", h[i].node->word ,  h[i].node->meaning ,  h[i].node->synonym ,  h[i].node->antonym);
       puts("\n");
   }


   fclose (fp);           // close the file
}



void print_hash(Hash  *t, int size ){     // print the hash function

    int i =0 ;
    printf("\n\tHashValue = (HashValue<<2 + (long long)(str[i]-60)) \n") ;


    for(i=0 ; i <size ; i++)
    {
        if(t[i].vis == 1 && t[i].del == 0)
        {
            printf("\t%s :: hash Function is : %d\n", t[i].node->word , get_key( t[i].node->word,size ) );
        }
    }
}


Hash* add_to_table(Tree root, Hash * h, int size  ){ // add word to the table

    if(root == NULL)
        return h ;
    else
    {
        add_to_table(root->Left, h,size ) ;

        Word temp = root->node ;

        h = insert_hash(temp, size, h) ;

        add_to_table(root->Right, h,size) ;
        return h ;
    }
}

Hash *implement_table( Tree root , int avlsize){ // create table


    Hash* h = create_table(avlsize);
    h = add_to_table(root, h, avlsize ) ;



    return h ;
}




