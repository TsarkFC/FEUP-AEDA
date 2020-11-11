/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//
#include <algorithm>
void ReadingClub::generateCatalog() {
    /*adiciona ao catálogo catalogItems novos itens de catálogo para os livros do vector books. Os itens
do catálogo (objetos da classe BookCatalogItem) estão organizados na BST alfabeticamente, pelo
título do livro e pelo autor do livro. Poderá haver livros com mesmo título, mas de autores diferentes –
isto implicará itens distintos no catálogo. Cada item do catálogo agrupa no vector items, da classe
BookCatalogItems, todos os livros de mesmo título e autor, independentemente do seu ano de edição.*/

    vector<BookCatalogItem> cat;

    for (int i = 0; i < books.size(); i++){
        if (find(cat.begin(), cat.end(), BookCatalogItem(books[i]->getTitle(), books[i]->getAuthor(), books[i]->getYear())) != cat.end()){
            //Gets vector
            vector<Book*> vec = find(cat.begin(), cat.end(), BookCatalogItem(books[i]->getTitle(), books[i]->getAuthor(), books[i]->getYear()))->getItems();
            //Changes the vector
            vec.push_back(books[i]);
            find(cat.begin(), cat.end(), BookCatalogItem(books[i]->getTitle(), books[i]->getAuthor(), books[i]->getYear()))->setItems(vec);
        }
        else {
            //Set existing values
            BookCatalogItem book_item(books[i]->getTitle(), books[i]->getAuthor(), books[i]->getYear());
            vector<Book*> initial = {books[i]};
            book_item.setItems(initial);
            cat.push_back(book_item);

        }
    }
    for (auto item:cat) catalogItems.insert(item);
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
    vector<Book*> ret;

	for (auto liv:books){
	    if (liv->getTitle() == book->getTitle() && liv->getAuthor() == book->getAuthor()){
	        if (liv->getReader() == NULL) ret.push_back(liv);
	    }
	}
	return ret;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
    BSTItrIn<BookCatalogItem> tree(catalogItems);

    while(!tree.isAtEnd()){
        //Found wanted book
        if (tree.retrieve().getAuthor() == book->getAuthor() && tree.retrieve().getTitle() == book->getTitle()){
            //Go through books
            for (auto liv:tree.retrieve().getItems()){
                if (liv->getReader() == NULL){
                    liv->setReader(reader);
                    reader->addReading(book->getTitle(), book->getAuthor());
                    return true;
                }
            }
        }
        tree.advance();
    }
    return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	userRecords.insert(user);
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	userRecords.erase(user);
	user->setEMail(newEMail);
	userRecords.insert(user);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
    for (auto person:candidates) {
        if (get<0>(person.getReading()) != "") {
            if (person.getReadings().size() + 1 >= min) readerCandidates.push(person);
        }
        else if (person.getReadings().size() >= min) readerCandidates.push(person);
    }
}

int ReadingClub::awardReaderChampion(User& champion) {
	priority_queue<User> copy = readerCandidates;

	if (copy.empty()) return 0;

	User first = copy.top();
	copy.pop();
	User second = copy.top();

	if (first == second) return 0;

	champion = first;
	return readerCandidates.size();
}
























