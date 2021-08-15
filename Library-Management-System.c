#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//	Nama 	: Leandra Ayudhia Alvaneza
//	Kelas	: LC01
//	NIM		: 2301885011

struct book //untuk menyimpan data buku
{
	int no_entri; //tajuk entri
	char author[4]; //tajuk_judul
	char judul_buku; //huruf_judul
	char borrower[10]; //nama peminjam
	struct book *right;
	struct book *left;
};

int no_entri = NULL; //tajuk entri
int choice, entri, input;
int no_search, x; //tajuk 

typedef struct date //deklarasi waktu
{
	int dd;
	int mm;
	int yy;
}date;
date start;				// m = mulai
date end;				// s = selesai
int dayS;				// jumlah hari mulai
int dayE;				// jumlah hari selesai
int dayDiff;			// selisih dalam bentuk hari
int year, month, day;	// selisih dalam berikut

struct book *createNode(b) //membuat node yang akan dimasukan ke dalam tree
{ 
	char author_b[4];
	struct book* createNode = malloc(sizeof(struct book));
	createNode->no_entri=b;
	fflush(stdin); //untuk membersihkan dan memindahkan data pada console
	printf("Enter Author name: "); 
	gets(author_b); //untuk dimasukan ke dalam char
	strcpy(createNode->author, author_b); //mencopy string ke dalam string lain
	printf("Enter the first letter of the title: "); 
	scanf("%c", &createNode->judul_buku);
	printf("\nThe book is inserted\n");
	printf("____________________________________________");
	createNode->left=NULL;
	createNode->right=NULL;
	
	return createNode;
}

struct borrower //untuk data pemimjam yang akan disimpan dalam linked list
{
	char borrower[10]; //nama peminjam
	char dayS; //keterangan waktu
	int value;
	struct book *book;
	struct borrower *next; //next adalah yang selanjutnya muncul 
};

typedef struct borrower node; // mengubah borrower menjadi node


node *create_new_node(int value) //membuat linked list
{
	node *result=malloc(sizeof(node));
	result->value=value;
	result->next=NULL;
	return result;
}


struct book* insert(struct book *root, int b) //untuk insert data yang akan dimasukan kedalam bst
{
	if(root==NULL) //jika root nya tidak ada, akan mencari tempat untuk insert
	{
		return createNode(b);
		
	}
	else if(b<root->no_entri) //kalau b lebih kecil maka harus di insert ke tree yang di kiri
	{
		root->left=insert(root->left,b);
	}
	   	
	else if(b>root->no_entri) //kalau b lebih besar maka harus di insert ke tree yang di kanan
	{
		root->right=insert(root->right,b);
	}
	   	
	else
	{
		printf("\nDuplicate number are not allowed!\n");
		printf("Please restart again!\n");
		
	}
	return root;
}  

void calculate_fee(b)
{
	int fee;
	int dayDriff;
	fee = 1000;
	dayS = start.dd + (start.mm * 30) + (start.yy * 365); //selisih dalam hari
	dayE = end.dd + (end.mm * 30) + (end.yy * 365);
	dayDiff = dayE - dayS;
	year = dayDiff / 365; // selisih dalam tahun, bulan, hari
	month = (dayDiff % 365) / 30;
	day = dayDiff - (year * 365 + month * 30);
	if (dayDriff > 1, day)
	{
		printf("The charge is", fee*dayDriff, day);
	}
}

void inorder(struct book *root) //fungsi untuk menampilkan tree
{
	if(root!=NULL) //mengecek apakah root bukan null
	{
		printf("\nBook List\n");
		printf("The entry number: %d\n", root->no_entri);
		printf("Author's name is: %s\n", root->author);
		printf("The first letter of the title: %c\n", root->judul_buku);
		inorder(root->left); //cek pada left child
        inorder(root->right); //cek pada right child
	}
}

struct book* FindMin(struct book* root) //mencari nilai min pada tree
{
	while(root->left != NULL) 
	{
		root = root->left;
	}
	return root;
};

struct book* Delete(struct book *root, int b) //menghapus data pada tree
{
	//memindahkan node dari tree ke dalam linked list
	node *head, *tmp;
	int i, n, x, del;
	i = 0;
	printf("\nEnter the entry number of the book you want to lend: ", i+1);
	scanf("%d", &n,"\n");
	printf("Enter borrow date with this format dd/mm/yy : ");
	scanf("%d/%d/%d", &start.dd, &start.mm, &start.yy);
	tmp =create_new_node(n); //
	head = tmp;	

	//mencari node dalam tree yang akan di hapus	
	if(root == NULL) //jika root kosong
	{
		return NULL; 
	}
	else if(b < root->no_entri)  //kalau b lebih besar maka mencari ke tree yang di kanan
	{
		root->left = Delete(root->left,no_entri);
	}
	else if (b> root->no_entri) //kalau b lebih kecil maka mencari ke tree yang di kiri
	{
		root->right = Delete(root->right,no_entri);
	}	
	else 
	{
		if(root->left == NULL && root->right==NULL) //tidak ada child
		{ 
			free(root);
			return NULL;
		}
		else if(root->left == NULL || root->right==NULL) //satu child
		{
			struct book *temp = NULL;
			if(root->left==NULL)
			{
				temp = root->left;
			}
			else
			{
				temp = root->left;
			}
			free(root);
			return temp;
		}
		else //dua child
		{ 
			struct book *temp = FindMin(root->right);
			root->no_entri = temp->no_entri;
			root->right = Delete(root->right,temp->no_entri);
		}
	}
	return root;
	
}

struct book* search(struct book* root, int b) //mencari buku pada tree
{
    if(root==NULL) //jika root nya null maka root akan print
    {
    	printf("\nBOOK NOT FOUND!\n");
	}
	else if(b>root->no_entri) // kalau b yang dicari lebih besar dari root maka akan mencari ke kanan
    {
    	return search(root->right, b);
	}
    else if(b<root->no_entri) // kalau b yang dicari kecil kecil dari root maka akan mencari ke kiri
    {
    	return search(root->left,b);
	}
	else if(b==root->no_entri)
    {
    	printf("\nBOOK FOUND!\n"); 
    	printf("The entry number: %d\n", root->no_entri);
		printf("Author's name is: %s\n", root->author);
		printf("The first letter of the title: %c\n", root->judul_buku);
	}
}

void Return(struct borrower* head) //fungsi untuk menghapus node pada linked list
{
	int i, n, x, del;
	i = 0;
	struct borrower *curr = head;
	printf("Enter the entry number of the book to be returned: "); 
	scanf("%d", &x);
	printf("Enter date of return with this format dd/mm/yy : ");
	scanf("%d/%d/%d", &end.dd, &end.mm, &end.yy);
	if (head->value==x)
	{
		head = head->next;
		free(curr);
	}
	else
	{
		while (curr->next->value != x) 
		{
			curr = curr ->next;
		}
		struct borrower *del = curr->next;
		curr->next =del->next;
		free(del);
	}
	calculate_fee();
	printf("The book has been returned");
}



int main(int argc, char *argv[])
{
	struct book* root = NULL;
		
	while(1)
	{
		printf("\nMAIN MENU\n1. Insert book\n2. Search book\n3. Borrow book\n4. Return book\n5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				if (choice == 1)
				{
					printf("\nHow many books do you want to input?: ");
					scanf("%d", &input);
					if (input > 1) 
					{
						int i;
						for(i=0;i<input;i++)
						{
							printf("\nEnter the entry number: ");
							scanf("%d",&entri);
							root=insert(root,entri);
						}
					} 
					else 
					{
						printf("\nEnter the entry number: ");
						scanf("%d",&entri);
						root=insert(root,entri);	
					}
				}
				
				break;
			case 2:
				printf("\nEnter the entry number that you want to search: "); //masukan nomor entri buku yang akan di cari
				scanf("%d", &no_search);
				search(root, no_search);
				break;
			case 3:
				inorder(root);
				if (root == NULL) // jika root dari tree nya kosong
				{ 
			        printf("Book is Empty!\n");
			    }
				root = Delete(root, entri);
				break;
			case 4:
				printf("Enter the entry number of the book to be returned: "); 
				scanf("%d", &x);
				printf("Enter date of return with this format dd/mm/yy : ");
				scanf("%d/%d/%d", &end.dd, &end.mm, &end.yy);
//				Return();
				break;
			case 5:
				exit(1);		
			default :
				printf("\n Wrong Input\n"); //yang di input tidak sesuai
		}
	}
}

