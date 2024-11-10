#include <iostream>
#include <string>
#include <stdio.h> 
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Khai bao cau truc Player
typedef struct Player {
    int ID; // ID cua nguoi choi
    string name; // Ten nguoi choi
    string password; // Mat khau nguoi choi
    long long int donate; // So tien donate
    long long int WIN; // So tran thang
    bool VIP; // Trang thai VIP
    bool suspicious; // Trang thai suspicious
} pl;

// Khai bao cau truc Node
struct Node {
    pl data; // Du lieu cua nguoi choi
    Node *next; // Con tro toi nut ke tiep
};

// Khai bao cau truc danh sach
typedef struct List {
    Node *head; // Con tro toi nut dau danh sach
    Node *tail; // Con tro toi nut cuoi danh sach
    int size; // Kich thuoc cua danh sach
    List(); // Ham khoi tao
    Node *createNode(pl x); // Tao mot nut moi
    bool isEmpty(); // Kiem tra danh sach co rong hay khong
    void addLast(Node *p); // Them nguoi choi vao cuoi danh sach
    bool checkID(int ID); // Kiem tra ID ton tai trong danh sach
    Node* find(int ID, string password); // Tim kiem nguoi choi (dang nhap)
    void donate(Node *currentPlayer); // Ham donate tien
    void vip(Node *currentPlayer); // Ham mua VIP
    void showList(Node *p);
	void showList(); // Hien thi danh sach nguoi choi
    void checkSuspicious(); // Kiem tra nguoi choi co dang nghi ngo khong
    void showSuspicious(); // Hien thi danh sach nguoi choi nghi ngo
    void showNoSuspicious(); // Hien thi danh sach nguoi choi khong nghi ngo
    void deleteSuspicious(Node *currentPlayer); // Xoa nguoi choi nghi ngo
} List;

// Ham khoi tao danh sach
List::List() {
    head = tail = NULL;
    size = 0;
}

// Ham tao mot nut moi
Node* List::createNode(pl x) {
    Node *p = new Node;
    p->data = x;
    p->next = NULL;
    return p;
}

// Ham kiem tra danh sach co rong hay khong
bool List::isEmpty() {
    return head == NULL; // Tra ve true neu danh sach rong
}

// Ham them nguoi choi vao cuoi danh sach
void List::addLast(Node *p) {
    if (isEmpty()) {
        head = tail = p; // Neu danh sach rong, gan ca head va tail cho nut moi
    } else {
        tail->next = p; // Gan nut moi vao cuoi danh sach
        tail = p; // Cap nhat tail
    }
    size++; // Tang kich thuoc danh sach
}

// Ham kiem tra ID
bool List::checkID(int ID) {
    for (Node *p = head; p != NULL; p = p->next) {
		if (p->data.ID == ID) {
            return true; // Tra ve true neu tim thay ID
        }
    }
    return false; // Tra ve false neu khong tim thay ID
}

// Ham tim kiem nguoi choi (dang nhap)
Node* List::find(int ID, string password) {
    for (Node *p = head; p != NULL; p = p->next) {
        if (p->data.ID == ID && p->data.password == password) {
            cout << "Dang nhap thanh cong! Chao mung " << p->data.name << "!" << endl;
            return p; // Tra ve Node tim thay
        }
    }
    cout << "ID hoac mat khau khong dung!" << endl;
    return NULL; // Tra ve NULL neu khong tim thay
}

// Ham donate tien
void List::donate(Node *currentPlayer) {
    int money;
    do {
        cout << "========== DONATE ==========" << endl;
        cout << "Hay nhap so tien ban muon donate (nhap 0 de quay lai): "; 
        cin >> money;

        if (money == 0) {
            cout << "Quay lai thong tin nguoi dung." << endl;
            return;
        }
        if (money > 0) {
            currentPlayer->data.donate += money; // Cong tien donate vao nguoi choi
            cout << "DONATE SUCCESS!!!" << endl << endl; 
            cout << "Nhan Enter de quay lai!!!" << endl;
            cin.ignore();
            cin.get(); // Cho nhan Enter
            return;
        } else {
            cout << "So tien khong hop le! Vui long nhap lai." << endl;
        }
    } while (true); // Lap lai cho den khi donate thanh cong
}

// Ham hien thi thong tin nguoi dung
void showUserInfo(Node* currentPlayer) {
    if (currentPlayer) {
        cout << "===== THONG TIN NGUOI DUNG =====" << endl << endl;
        cout << "ID: " << currentPlayer->data.ID << endl; 
        cout << "Name: " << currentPlayer->data.name << endl; 
        cout << "Donate: " << currentPlayer->data.donate << endl; 
        cout << "WIN: " << currentPlayer->data.WIN << endl; 
        cout << "VIP: " << (currentPlayer->data.VIP ? "Yes" : "No") << endl; 
        cout << "Suspicious: " << (currentPlayer->data.suspicious ? "Yes" : "No") << endl; 
    }
}

// Ham mua VIP
void List::vip(Node *currentPlayer) {
    int choose;
    if(currentPlayer->data.VIP == true){
    	cout << "You already buy VIP" << endl;
	}
	else if (currentPlayer->data.donate >= 500000) {
        cout << "========== VIP ==========" << endl << endl;
        cout << "Ban co chac muon mua VIP?" << endl;
        cout << "1. Yes" << endl;
        cout << "0. No" << endl;
        cout << "Hay nhap lua chon cua ban: "; 
        cin >> choose;

        if (choose == 1) {
            currentPlayer->data.donate -= 500000;
            currentPlayer->data.VIP = true;
            cout << "BUY VIP SUCCESS!!!" << endl;
        }
    } 
	else {
        cout << "Donate cua ban khong du!" << endl;
    }
    cout << endl; 
    cout << "Nhan Enter de quay lai!!!" << endl;
    cin.ignore();
    cin.get(); // Cho nhan Enter de quay lai
}

// Ham sap xep theo donate giam dan
void bubbleSortDonate(Node* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j]->data.donate < arr[j + 1]->data.donate) {
                swap(arr[j], arr[j + 1]); // Hoan doi neu donate o truoc nho hon donate o sau
            }
        }
    }
}

void bubbleSortWin(Node* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j]->data.WIN < arr[j + 1]->data.WIN) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void showTopWin(List& playerList, int topN) {
    const int maxPlayers = 100;
    Node* players[maxPlayers];
    int count = 0;

    // Luu danh sach nguoi choi vao mang
    for (Node* p = playerList.head; p != NULL && count < maxPlayers; p = p->next) {
        players[count++] = p;
    }

    // Sap xep danh sach theo so lan thang
    bubbleSortWin(players, count);

    // In tieu de bang
    printf("+-----+------------+-------------------------+-----------+\n");
    printf("| Top |     ID     |          Name           |    WIN    |\n");
    printf("+-----+------------+-------------------------+-----------+\n");

    // In thong tin cac nguoi choi
    for (int i = 0; i < min(topN, count); i++) {
        printf("| %-3d | %-10d | %-23s | %-9lld |\n",  
               i + 1,  
               players[i]->data.ID,  
               players[i]->data.name.c_str(),  
               players[i]->data.WIN);  
    }
    
    printf("+-----+------------+-------------------------+-----------+\n");
}

void showTopDonate(List& playerList, int topN) {
    const int maxPlayers = 100;
    Node* players[maxPlayers];
    int count = 0;

    // Luu danh sach nguoi choi vao mang
    for (Node* p = playerList.head; p != NULL && count < maxPlayers; p = p->next) {
        players[count++] = p;
    }

    // Sap xep danh sach theo so tien quyen gop
    bubbleSortDonate(players, count);

    // In tieu de bang
    printf("+-----+------------+-------------------------+---------------------------+\n");
    printf("| Top |     ID     |          Name           |          Donate           |\n");
    printf("+-----+------------+-------------------------+---------------------------+\n");

    // In thong tin cac nguoi choi
    for (int i = 0; i < min(topN, count); i++) {
        printf("| %-3d | %-10d | %-23s | %-25lld |\n",
               i + 1,  
               players[i]->data.ID,  
               players[i]->data.name.c_str(),  
               players[i]->data.donate);  
    }

    printf("+-----+------------+-------------------------+---------------------------+\n");
}

void List::showList(Node* p) {
    if (p == NULL) {
        return; // Dung lai khi het danh sach
    }

    // Hien thi thong tin cua node hien tai
    cout << "-----------------------------" << endl;
    cout << endl;
    cout << "ID: " << p->data.ID << endl; 
    cout << "Ten dang nhap: " << p->data.name << endl; 
    cout << "Password: " << p->data.password << endl; 
    cout << "Donate: " << p->data.donate << endl; 
    cout << "WIN: " << p->data.WIN << endl; 
    cout << "VIP: " << (p->data.VIP ? "Yes" : "No") << endl; 
    cout << "Suspicious: " << (p->data.suspicious ? "Yes" : "No") << endl;
    cout << "-----------------------------" << endl; 

    // Duyet de quy cho node tiep theo
    showList(p->next);
}

// Ham showList duoc goi tu ngoai voi head la tham so
void List::showList() {
    showList(head);
}


void List::checkSuspicious() {
    int found = 0;  
    int checkID;
    do {
        cout << "Hay nhap ID ban muon nghi van suspicious: "; 
        cin >> checkID;
    } while (checkID <= 0);

    for (Node *p = head; p != NULL; p = p->next) {
        if (p->data.ID == checkID) {
            p->data.suspicious = true;
            found = 1;  
            cout << "-----------------------------" << endl;
            cout << endl;
            cout << "ID: " << p->data.ID << endl; 
            cout << "Ten dang nhap: " << p->data.name << endl; 
            cout << "Password: " << p->data.password << endl; 
            cout << "Donate: " << p->data.donate << endl; 
            cout << "WIN: " << p->data.WIN << endl; 
            cout << "VIP: " << (p->data.VIP ? "Yes" : "No") << endl; 
            cout << "Suspicious: " << (p->data.suspicious ? "Yes" : "No") << endl;
            cout << "-----------------------------" << endl; 
            break; 
        }
    }

    // Kiem tra neu khong tim thay ID
    if (!found) {
        cout << "Khong co ID nguoi choi nhu vay" << endl;
    }
}

void List::showSuspicious() {
    int suspicious = 0; 

    for (Node *p = head; p != NULL; p = p->next) {
        if (p->data.suspicious) { 
            suspicious = 1;  
            cout << "-----------------------------" << endl;
            cout << "ID: " << p->data.ID << endl; 
            cout << "Ten dang nhap: " << p->data.name << endl; 
            cout << "Password: " << p->data.password << endl; 
            cout << "Donate: " << p->data.donate << endl; 
            cout << "WIN: " << p->data.WIN << endl; 
            cout << "VIP: " << (p->data.VIP ? "Yes" : "No") << endl; 
            cout << "Suspicious: " << (p->data.suspicious ? "Yes" : "No") << endl;
            cout << "-----------------------------" << endl; 
        }
    }

    if (suspicious == 0) {
        cout << "Khong co nguoi choi nao nghi van!" << endl;
    }
}

void List::showNoSuspicious() {
    bool found = false; 

    for (Node *p = head; p != NULL; p = p->next) {
        if (!p->data.suspicious) {  
            found = true;  
            cout << "-----------------------------" << endl;
            cout << "ID: " << p->data.ID << endl; 
            cout << "Ten dang nhap: " << p->data.name << endl; 
            cout << "Password: " << p->data.password << endl; 
            cout << "Donate: " << p->data.donate << endl; 
            cout << "WIN: " << p->data.WIN << endl; 
            cout << "VIP: " << (p->data.VIP ? "Yes" : "No") << endl; 
            cout << "Suspicious: " << (p->data.suspicious ? "Yes" : "No") << endl;
            cout << "-----------------------------" << endl; 
        }
    }

    if (!found) {
        cout << "Khong co nguoi choi nao khong bi nghi van!" << endl;
    }
}

void List::deleteSuspicious(Node* currentPlayer) {
    int choice;

    while (true) {
        cout << "Hay nhap ID nguoi choi nghi van ban muon xoa (nhan 0 de quay lai): "; 
        cin >> choice;

        // Neu nguoi dung nhap 0, thoat khoi vong lap
        if (choice == 0) {
            cout << "Quay lai menu admin." << endl;
            return;
        }

        Node *prev = NULL;
        Node *current = head;
        bool found = false; // Bien de kiem tra neu da tim thay nguoi choi

        while (current != NULL) {
            if (current->data.ID == choice) {
                if (current->data.suspicious) { // Kiem tra nguoi choi co nghi van khong
                    if (current == currentPlayer) { // Kiem tra xem nguoi choi co phai la nguoi dang dang nhap khong
                        cout << "Khong the xoa tai khoan dang dang nhap!" << endl;
                        found = true; // Da tim thay nhung khong the xoa
                        break; // Thoat khoi vong lap de yeu cau nhap lai
                    }

                    if (prev == NULL) {
                        head = current->next; // Neu xoa phan tu dau danh sach
                    } else {
                        prev->next = current->next; // Xoa phan tu giua
                    }
                    
                    if (current == tail) {
                        tail = prev; // Cap nhat tail neu xoa phan tu cuoi
                    }

                    delete current; // Giai phong bo nho
                    size--; // Giam kich thuoc danh sach
                    cout << "Xoa nguoi choi ID " << choice << " thanh cong!" << endl;
                    found = true; // Da xoa thanh cong
                    break; // Thoat khoi vong lap
                } else {
                    cout << "Nguoi choi ID " << choice << " khong co nghi van!" << endl;
                    found = true; // Da tim thay nhung khong co nghi van
                    break; // Thoat khoi vong lap de yeu cau nhap lai
                }
            }
            prev = current;
            current = current->next;
        }

        // Neu khong tim thay ID
        if (current == NULL) {
            cout << "Khong tim thay nguoi choi voi ID " << choice << "!" << endl;
            found = true; // Da tim thay nhung khong co nguoi choi
        }

        // Neu chua tim thay nguoi choi thi tiep tuc yeu cau nhap
        if (!found) {
            continue; // Lap lai vong lap chinh de yeu cau nhap ID moi
        }
    }
}

void saveDataToFile(const List& playerList) {
    std::ofstream file("playerProfile1.txt"); // Mo file de ghi
    if (file.is_open()) {
        Node* p = playerList.head;
        while (p != NULL) {
            file << p->data.ID << " "
                 << p->data.name << " "
                 << p->data.password << " "
                 << p->data.donate << " "
                 << p->data.WIN << " "
                 << p->data.VIP << " "
                 << p->data.suspicious << std::endl;
            p = p->next;
        }
        file.close();
    } else {
        std::cout << "Khong mo duoc tep de ghi!" << std::endl;
    }
}

void loadDataFromFile(List& playerList) {
    std::ifstream file("playerProfile1.txt"); // Mo file de doc
    if (file.is_open()) {
        while (!file.eof()) {
            pl newPlayer;
            file >> newPlayer.ID;
            file.ignore();
            std::getline(file, newPlayer.name, ' ');
            std::getline(file, newPlayer.password, ' ');
            file >> newPlayer.donate
                 >> newPlayer.WIN
                 >> newPlayer.VIP
                 >> newPlayer.suspicious;
            Node* p = playerList.createNode(newPlayer);
            playerList.addLast(p);
        }
        file.close();
    } else {
        std::cout << "Khong mo duoc tep de doc!" << std::endl;
    }
}

const int BOARD_SIZE = 9; // Ban co co 9 o
char board[BOARD_SIZE];

// Khoi tao ban co rong
void initBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = '1' + i; // Gan cac vi tri tu 1 den 9
    }
}

// In ra ban co voi can giua, gach hang cot day du va vien ngoai
void printBoard() {
    cout << " ======================================================================================================================" << endl;
    cout << "\t\t\t\t\t\t  *******************" << endl;
    cout << "\t\t\t\t\t\t  *     |     |     *" << endl;
    cout << "\t\t\t\t\t\t  *  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "  *" << endl;
    cout << "\t\t\t\t\t\t  *_____|_____|_____*" << endl;
    cout << "\t\t\t\t\t\t  *     |     |     *" << endl;
    cout << "\t\t\t\t\t\t  *  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "  *" << endl;
    cout << "\t\t\t\t\t\t  *_____|_____|_____*" << endl;
    cout << "\t\t\t\t\t\t  *     |     |     *" << endl;
    cout << "\t\t\t\t\t\t  *  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "  *" << endl;
    cout << "\t\t\t\t\t\t  *     |     |     *" << endl;
    cout << "\t\t\t\t\t\t  *******************" << endl;
}

// Kiem tra nuoc di co hop le khong
bool isValidMove(int move) {
    return move >= 1 && move <= 9 && board[move - 1] != 'X' && board[move - 1] != 'O';
}

// Kiem tra xem co ai thang khong
char checkWin() {
    // Kiem tra cac hang
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == board[i + 1] && board[i + 1] == board[i + 2]) return board[i];
    }
    // Kiem tra cac cot
    for (int i = 0; i < 3; i++) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) return board[i];
    }
    // Kiem tra hai duong cheo
    if (board[0] == board[4] && board[4] == board[8]) return board[0];
    if (board[2] == board[4] && board[4] == board[6]) return board[2];

    // Kiem tra xem con o trong khong
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] != 'X' && board[i] != 'O') return '-';
    }

    return 'D'; // Hoa
}

// Nguoi choi nhap nuoc di
void playerMove() {
    int move;
    cout << "Nhap vi tri muon danh (1-9): ";
    cin >> move;
    while (!isValidMove(move)) {
        cout << "Nuoc di khong hop le!!! Nhap lai: ";
        cin >> move;
    }
    board[move - 1] = 'X';
}

// Kiem tra neu co the thang o buoc tiep theo
int findWinningMove(char player) {
    // Kiem tra tat ca cac o de tim nuoc di co the thang
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char temp = board[i];
            board[i] = player; // Dat quan co tam thoi
            if (checkWin() == player) {
                board[i] = temp; // Dat lai nhu cu
                return i + 1;    // Tra ve nuoc di thang
            }
            board[i] = temp; // Dat lai nhu cu
        }
    }
    return -1; // Khong tim thay nuoc di thang
}

// May tinh chon nuoc di chien luoc
void computerMove() {
    // Tim nuoc di ma may co the thang
    int move = findWinningMove('O');
    if (move != -1) {
        board[move - 1] = 'O';
        cout << "May da danh vao o:  " << move << endl;
        return;
    }

    // Neu khong co nuoc thang, kiem tra xem nguoi choi co the thang khong va chon
    move = findWinningMove('X');
    if (move != -1) {
        board[move - 1] = 'O';
        cout << "May da danh vao o: " << move << endl;
        return;
    }

    // Neu khong co nuoc di chien luoc, chon ngau nhien
    do {
        move = rand() % 9 + 1;
    } while (!isValidMove(move));
    board[move - 1] = 'O';
    cout << "May da danh vao o: " << move << endl;
}

void clearScreen() {
    // In ra khoang trong de tao cam giac "xoa man hinh"
    for (int i = 0; i < 100; ++i) {
        cout << endl; // In 100 dong trong
    }
}

int main() {
    List playerList;
    loadDataFromFile(playerList);
    int choose;
    int leave = 0;
    Node* currentPlayer = NULL; // Khai bao Node cho nguoi choi hien tai

    do {
        clearScreen();
		// Hien thi menu chinh cho nguoi dung dang nhap hoac dang ki  
		cout << "========== MENU ==========" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Hay nhap lua chon cua ban: "; 
        cin >> choose;

        switch (choose) {
            case 1: {
				pl newPlayer;
                clearScreen();
				cout << "========== REGISTER ==========" << endl;
                cout << "Nhap 0 vao ID de quay lai menu chinh!!!" << endl << endl;
				do {
					cout << "Nhap ID(chi nhap bang so): "; 
					cin >> newPlayer.ID;
					if (newPlayer.ID < 0){
						cout << "ID khong hop le!!! Vui long nhap lai!!!" << endl << endl;
					}
        			else if (playerList.checkID(newPlayer.ID)) {
            			cout << "ID da ton tai! Vui long nhap ID khac." << endl << endl;
        			}
    			} while (playerList.checkID(newPlayer.ID)||newPlayer.ID < 0); // Lap lai neu ID da ton tai
                if(newPlayer.ID == 0){
                	break;
				}
				cin.ignore(); // Loai bo ky tu newline sau ID
                cout << "Nhap Ten: "; 
                getline(cin, newPlayer.name); 
                cout << "Nhap Password: "; 
                getline(cin, newPlayer.password); 
                newPlayer.donate = 0; 
                newPlayer.WIN = 0;    
                newPlayer.VIP = false; 
                newPlayer.suspicious = false; 

                Node *p = playerList.createNode(newPlayer);
                playerList.addLast(p);
                saveDataToFile(playerList);
                break;
                clearScreen();
            }
            case 2: {
                int ID; 
                string password;
                clearScreen();
                cout << "========== LOGIN ==========" << endl << endl;
				cout << "Nhap ID: "; cin >> ID; 
                cin.ignore(); // De xoa newline sau ID
                cout << "Nhap mat khau: "; 
                getline(cin, password);  
                
				currentPlayer = playerList.find(ID, password); // Luu Node nguoi choi vao currentPlayer
                if (currentPlayer != NULL) { // Neu dang nhap thanh cong
                    // Menu sau khi dang nhap
                    do {
                        clearScreen();
						cout << endl;
                        showUserInfo(currentPlayer); // Hien thi lai thong tin nguoi dung
                        cout << "==============================" << endl;
                        cout << "1. Play" << endl;
                        cout << "2. Home" << endl;
                        cout << "3. Donate" << endl;
                        cout << "4. VIP (500.000$)" << endl;
                        cout << "5. ADMINISTRATOR" << endl;
                        cout << "0. LOG OUT" << endl;
                        cout << "Hay nhap lua chon cua ban: "; 
                        cin >> choose;

                        switch (choose) {
                            case 1:
                                {
								clearScreen();
								srand(time(0));  // Khoi tao so ngau nhien 1 lan duy nhat
							    initBoard();
							    char winner = '-';
							    while (winner == '-') {
							        printBoard();
							        playerMove();
							        clearScreen();
							        winner = checkWin();
							        if (winner != '-') break;
							        computerMove();
							        winner = checkWin();
							    }
							
							    printBoard();
							
							    if (winner == 'X') {
							        cout << "YOU WIN !!!" << endl;
							        currentPlayer->data.WIN += 1;
							    } else if (winner == 'O') {
							        cout << "YOU LOSE !!!" << endl;
							    } else {
							        cout << "DRAW !!!" << endl;
							    }
								saveDataToFile(playerList);
								cout << endl;
								cout << "Nhan Enter de quay lai!!!" << endl;
                       			cin.ignore();
                        		cin.get(); // Cho phep nguoi dung nhan Enter
                                break;
                            }
                            case 2:
                                clearScreen();
								cout << "========== HOME ==========" << endl << endl;
                                cout << "1. Huong dan choi" << endl;
                                cout << "2. TOP WIN" << endl;
                                cout << "3. TOP DONATE" << endl;
                                cout << "0. BACK" << endl; 
                                cout << "Hay nhap lua chon cua ban: "; 
                                cin >> choose;
                                switch(choose) {
                                    case 1:
                                        clearScreen();
										cout << "===== HUONG DAN NGUOI CHOI =====" << endl << endl;
                                        cout << "1. Khi bat dau tro choi, tro choi se ngau nhien quyet dinh X hoac O di truoc. " << endl;
                                        cout << "2. Ban la X, con` may la` O." << endl;
                                        cout << "3. Neu ban danh duoc 3 diem nam` tren 1 duong thang hoac cheo thi ban thang." << endl;
                                        cout << "\t+---+---+---+   +---+---+---+   +---+---+---+" << endl;
                                        cout << "\t| X | X | X |   | X |   |   |   | X |   |   |" << endl;
                                        cout << "\t+---+---+---+   +---+---+---+   +---+---+---+" << endl;
                                        cout << "\t|   |   |   |   | X |   |   |   |   | X |   |" << endl;
                                        cout << "\t+---+---+---+   +---+---+---+   +---+---+---+" << endl;
                                        cout << "\t|   |   |   |   | X |   |   |   |   |   | X |" << endl;
                                        cout << "\t+---+---+---+   +---+---+---+   +---+---+---+" << endl;
                                        cout << "4. Va` nguoc lai neu may danh duoc 3 diem nam tren 1 duong thang hoac cheo thi ban thua" << endl;
                                        cout << "5. Neu danh het ban co` ma` khong ai thang thi` ban hoa`" << endl << endl;
                                        cout << "Nhan Enter de quay lai!!!" << endl;
                                        cin.ignore();
                                        cin.get(); // Cho nhan Enter de quay lai
                                        break;
                                    case 2:
                                        clearScreen();
										cout << "===== TOP 5 WIN =====" << endl;
                                        showTopWin(playerList, 5);
                                        cout << "Nhan Enter de quay lai!!!" << endl;
                       					cin.ignore();
                        				cin.get(); // Cho phep nguoi dung nhan Enter
                                        break;
                                    case 3: 
                                        clearScreen();
										cout << "===== TOP 5 DONATE =====" << endl;
                                        showTopDonate(playerList, 5);
                                        cout << "Nhan Enter de quay lai!!!" << endl;
                       					cin.ignore();
                        				cin.get(); // Cho phep nguoi dung nhan Enter
                                        break;
                                    case 0:
                                        break;
                                    default:
                                       
										cout << "Lua chon khong hop le! Vui long nhap lai." << endl;
                                        break;
                                }
                                break;
                            case 3:
                                clearScreen();
								if (currentPlayer) {
                                    playerList.donate(currentPlayer); // Goi ham donate
                                }
                                saveDataToFile(playerList);
                                break;
                            case 4:
                                clearScreen();
								playerList.vip(currentPlayer); // Goi ham vip 
								saveDataToFile(playerList);
                                break;
                            case 5:
                            {
    							clearScreen();
								string adminPassword;
    							bool isAdmin = false; // Bien kiem tra trang thai Admin
    							do {
        							clearScreen();
									cout << "========== ADMIN PASSWORD ==========" << endl << endl;
									cout << "Nhap mat khau Admin(12345678): ";
        							cin >> adminPassword;
        							if (adminPassword == "12345678") {
            							isAdmin = true; // Ðat bien isAdmin thành true
           							while (isAdmin) {
                						clearScreen();
										cout << "========== ADMINISTRATOR ==========" << endl << endl;
                						cout << "1. Observe a list " << endl;
                						cout << "2. Check Suspicious " << endl;
                						cout << "3. Ban " << endl;
                						cout << "0. Back" << endl << endl; 
                						cout << "Hay nhap lua chon cua ban: "; 
                						cin >> choose;

                						switch (choose) {
                    						case 1:
                        						clearScreen();
												cout << "========== PLAYER'S LIST ==========" << endl << endl;
                        						playerList.showList();
                        						cout << "Nhan Enter de quay lai!!!" << endl;
                       							cin.ignore();
                        						cin.get(); // Cho phep nguoi dung nhan Enter
												break;
                    						case 2:
                    							clearScreen();
                        						cout << "========== CHECK SUSPICIOUS ==========" << endl << endl;
                        						playerList.showNoSuspicious();
												playerList.checkSuspicious();
												saveDataToFile(playerList);
                        						cout << "Nhan Enter de quay lai!!!" << endl;
                       							cin.ignore();
                        						cin.get(); //Cho phep nguoi dung nhan Enter
                        						break;
                    						case 3:
                    							clearScreen();
                    							cout << "========== SUSPICIOUS LIST========== " << endl << endl;
                    							playerList.showSuspicious();
                    							cout << endl << endl << endl;
                    							playerList.deleteSuspicious(currentPlayer);
                    							saveDataToFile(playerList);
                    							playerList.showSuspicious();
                    							break;
											case 0:
                        						isAdmin = false; // Dat isAdmin thành false de thoat khoi vong lap
												break;
                    						default:
												cout << "Lua chon khong hop le! Vui long nhap lai." << endl;
                        						break;    
                						}
            						}
        							} else {
            							cout << "Wrong Password!!!" << endl; 
        							}								
    							} while (adminPassword != "12345678");
    						break; // Them break de ra khoi case 5
							}
							case 0:
                                currentPlayer = NULL; // Dat lai nguoi choi hien tai
                                break;
                            default:
                                
								cout << "Lua chon khong hop le! Vui long nhap lai." << endl;
                                break;
                        }
                    } while (currentPlayer != NULL); // Tiep tuc cho den khi nguoi choi chon dang xuat
                }
                break;
            }
            case 0:
                cout << "Thoat chuong trinh." << endl;
                leave = leave + 1;
                break;  
            default:
                
				cout << "Lua chon khong hop le! Vui long nhap lai." << endl;
                break;
        }
    } while (leave == 0);
    
    return 0;
}

