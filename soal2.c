/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
 *   Modul               : 5
 *   Hari dan Tanggal    : Rabu, 13 Mei 2026
 *   Nama (NIM)          : Hufnagel Ruben Lenard Situmorang (13224015)
 *   Nama File           : soal2.c
 *   Deskripsi           : 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
    int sel;
    int check;
    struct node* atas;
    struct node* bawah;
    struct node* kiri;
    struct node* kanan;
};

struct node* newNode(int data){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp==NULL)
        return NULL;
    temp->sel = data;
    temp->check=0;
    return temp;
}

struct node* stack[1000];
int jumlah_stack = 0;

void push(struct node* x){
    stack[jumlah_stack] = x;
    jumlah_stack +=1;
}

struct node* pop(){
    jumlah_stack-=1;
    return stack[jumlah_stack+1];
}

int sum = 0;
int dfs(struct node* x, int size){
    struct node* temp = x;
    
    if (temp->sel!=0 && temp->check!=1){
        size += 1;
        temp->check = 1;
        if (temp->kanan->sel!=0 && temp->kanan->check!=1){
            push(temp->kanan);
        }
        if (temp->kiri->sel!=0 && temp->kiri->check!=1){
            push(temp->kiri);
        }
        if (temp->bawah->sel!=0 && temp->bawah->check!=1){
            push(temp->bawah);
        }
        if (temp->atas->sel!=0 && temp->atas->check!=1){
            push(temp->atas);
        }
        size += dfs(pop(), size);
        return size;
    }
    else{
        return 0;
    }
}

int terima_input(int input, int x, int C){
    input = input/(pow(10,C-(x+1)));
    input = input%10;
    return input;
}

int main(){
    int R, C;
    scanf("%d %d",&R, &C);

    int matrix[R][C];
    int sel_temp;
    for (int i=0;i<R;i++){
        scanf("%d",&sel_temp);
        for (int j=0;j<C;j++){
            int sel_temp1 = terima_input(sel_temp,j,C);
            matrix[i][j] = sel_temp1;
        }
    }

    struct node* R0C0 = newNode(matrix[0][0]);
    struct node* temp = R0C0;
    struct node* temp1;
    struct node* temp2;

    for (int i=0;i<C;i++){
        if (i!=0){
            temp->kanan->kiri = temp;
            temp = temp->kanan;
        }
        temp = newNode(matrix[0][i]);
        temp1 = temp;
        for (int j=1;j<R;j++){
            temp1->bawah->atas = temp1;
            temp1 = temp1->bawah;
            temp1 = newNode(matrix[j][i]);
            temp2 = temp1;
            temp2->kanan->kiri = temp2;
            temp2 = temp2->kanan;
        }
    }
    temp = R0C0;
    int size_besar = 0;
    for (int i=0;i<C;i++){
        int size = 0;
        size = dfs(temp,size);
        if (size>0){
            sum +=1;
            if (size>size_besar){
                size_besar = size;
            }
        }
        if (i!=0){
            temp = temp->kanan;
        }
        temp1=temp;
        for (int j=1;j<R;j++){
            size = 0;
            temp1 = temp1->bawah;
            size = dfs(temp1,size);
            if (size>size_besar){
                size_besar = size;
            }
        }
    }

    printf("ISLANDS %d\nLARGEST %d",sum,size_besar);
    return 0;
}
