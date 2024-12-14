// Paige Saychareun
// CWID: 884902354

#include<iostream>
#include<memory>
#include<vector>
#include<string>

// Template class for Tab
template <typename T>
class Tab {
public:
    std::string url;
    std::string name;
    T memory;
    Tab* next;
    Tab* prev;

    Tab(const std::string& url, const std::string& name, T memory)
        : url(url), name(name), memory(memory), next(nullptr), prev(nullptr) {}
};

// Template class for Browser
template <typename T>
class Browser {
private:
    Tab<T>* head;
    Tab<T>* tail;
    Tab<T>* current;
    std::vector<std::pair<std::string, std::string>> bookmarks;

public:
    Browser() : head(nullptr), tail(nullptr), current(nullptr) {}

    void addNewTab(const std::string& url, const std::string& name, T memory) {
        Tab<T>* newTab = new Tab<T>(url, name, memory);
        if (!head) {
            head = tail = current = newTab;
        } else {
            tail->next = newTab;
            newTab->prev = tail;
            tail = newTab;
            current = newTab;
        }
    }

    void switchToPrevTab() {
        if (current && current->prev) {
            current = current->prev;
            std::cout << "Switched to previous tab: " << current->name << " (" << current->url << ")" << std::endl;
        } else {
            std::cout << "No previous tab" << std::endl;
        }
    }

    void switchToNextTab() {
        if (current && current->next) {
            current = current->next;
            std::cout << "Switched to next tab: " << current->name << " (" << current->url << ")" << std::endl;
        } else {
            std::cout << "No next tab" << std::endl;
        }
    }

    void closeCurrentTab() {
        if (!current) return;

        Tab<T>* toDelete = current;
        if (current->next) {
            current = current->next;
            if (toDelete->prev) {
                toDelete->prev->next = current;
                current->prev = toDelete->prev;
            } else {
                head = current;
                current->prev = nullptr;
            }
        } else if (current->prev) {
            current = current->prev;
            current->next = nullptr;
            tail = current;
        } else {
            head = tail = current = nullptr;
        }

        std::cout << "Closed tab. Now the current tab = " << (current ? current->name : "None") << std::endl;
        delete toDelete;
    }

    void bookmarkCurrent() {
        if (!current) return;

        for (const auto& bookmark : bookmarks) {
            if (bookmark.first == current->name && bookmark.second == current->url) {
                std::cout << "The bookmark is already added!!" << std::endl;
                return;
            }
        }

        bookmarks.emplace_back(current->name, current->url);
        std::cout << "Bookmark added: " << current->name << " (" << current->url << ")" << std::endl;
    }

    void showBookmarkTab() {
        std::cout << "Bookmarks:" << std::endl;
        for (const auto& bookmark : bookmarks) {
            std::cout << bookmark.first << " (" << bookmark.second << ")" << std::endl;
        }
    }

    void moveCurrentToFirst() {
        if (!current || current == head) return;

        if (current->next) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }

        if (current->prev) {
            current->prev->next = current->next;
        }

        current->next = head;
        current->prev = nullptr;
        head->prev = current;
        head = current;

        std::cout << "Moved current tab to first position: " << current->name << std::endl;
    }

    T total_memory() {
        T total = 0;
        Tab<T>* temp = head;
        while (temp) {
            total += temp->memory;
            temp = temp->next;
        }
        return total;
    }

    void deleteTab() {
        if (!head) return;

        Tab<T>* maxTab = head;
        Tab<T>* temp = head;
        while (temp) {
            if (temp->memory > maxTab->memory) {
                maxTab = temp;
            }
            temp = temp->next;
        }

        std::cout << "Deleting tab: " << maxTab->name << " with memory " << maxTab->memory << "MB" << std::endl;

        if (maxTab->prev) {
            maxTab->prev->next = maxTab->next;
        } else {
            head = maxTab->next;
        }

        if (maxTab->next) {
            maxTab->next->prev = maxTab->prev;
        } else {
            tail = maxTab->prev;
        }

        if (current == maxTab) {
            current = maxTab->next ? maxTab->next : maxTab->prev;
        }

        delete maxTab;
    }

    void display() {
        Tab<T>* temp = head;
        std::cout << "Browser tab list: " << std::endl;
        while (temp) {
            std::cout << "| " << temp->name << " | --> ";
            temp = temp->next;
        }
        std::cout << "NULL" << std::endl;
    }
};



int main(){
/*Browser<double> b1;
b1.addNewTab("https://www.google.com","Google",23.45);
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to Next tab = "<<std::endl;
b1.switchToNextTab();
b1.addNewTab("https://www.youtube.com","YouTube",56);
b1.bookmarkCurrent();
b1.display();
b1.addNewTab("https://www.geeksforgeeks.com","GeeksForGeeks",45.78);
b1.bookmarkCurrent();
b1.addNewTab("https://chat.openai.com","ChatGPT",129);
b1.addNewTab("https://linkedin.com","LinkedIn",410);
b1.bookmarkCurrent();
b1.addNewTab("https://github.com","Github",110);
b1.addNewTab("https://kaggle.com","Kaggle",310);
b1.bookmarkCurrent();
b1.display();
std::cout<<"Total memory consumption = "<<b1.total_memory()<<"MB"<<std::endl;
b1.showBookmarkTab();
b1.moveCurrentToFirst();
b1.display();
b1.deleteTab();
b1.display();
std::cout<<"Switch to next tab = "<<std::endl;
b1.switchToNextTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
b1.showBookmarkTab();
std::cout<<"Total Memory Consumption = "<<b1.total_memory()<<"MB"<<std::endl;
b1.deleteTab();
b1.display();
b1.addNewTab("https://docs.google.com/","Google Docs",102.34);
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.bookmarkCurrent();
b1.showBookmarkTab();
b1.total_memory();
b1.deleteTab();
b1.display();*/
return 0;
}
