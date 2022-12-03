#include "RleString.h"
#include<stdexcept>

// TODO Write your implementation here
void RleString::compress(const std::string& str)
{
    size_t strSize = str.size();
    head = new Node(str[0],1);
    Node* LastNode = head;
    for (int i = 1 ; i < strSize ; i++)
    {
        if(str[i-1] != str[i])
        {
            Node* newNode = new Node(str[i],0);
            listLength += LastNode->count;
            LastNode->next = newNode;
            LastNode = LastNode->next;
        }
        LastNode->count++;
    }
    listLength += LastNode->count;
}
void RleString::copy(const RleString& other)
{   
    Node* current = nullptr;
    Node* nextNode = nullptr;
    if(!other.head) this->head = nullptr;
    else
    {
        head = new Node(other.head->symbol,other.head->count);
        current = this->head;
        nextNode = other.head->next;
    }
    while(nextNode)
    {
        current->next = new Node (nextNode->symbol,nextNode->count);
        current  = current->next;
        nextNode = nextNode->next;
    }
    this->listLength = other.listLength;
}
void RleString::free()
{
    while(head)
    {
        Node* current = head;
        head = head->next;
        delete current;
    }
    listLength = 0;
}
// public
RleString::RleString() : head(nullptr) , listLength(0)
{}
RleString::RleString(const std::string& str)
{
    if (str.empty())
    {
        RleString();
    }
    else
    {
        this->compress(str);
    }
}
RleString::RleString(const RleString& other)
{
    copy(other);
}
RleString& RleString::operator=(const RleString& other) 
{
    if(this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}
RleString::~RleString()
{
    free();
}
std::string RleString::toString () const
{
    if(!head) return "";
    Node* current = head;
    std::string resultString;
    while(current)
    {
        resultString.append(current->count,current->symbol);
        current = current->next;
    }
    return resultString;
}
bool RleString::operator==(const RleString& other) const
{
    Node* myHead = this->head;
    Node* otherHead = other.head;

    while(myHead && otherHead)
    {
        if(myHead->count != otherHead->count) return false;
        if(myHead->symbol != otherHead->symbol) return false;
        myHead = myHead->next;
        otherHead = otherHead->next;
    }

    if(!myHead && !otherHead) return true;
    return false;
}
bool RleString::operator==(const std::string& str) const
{   
    if(!head && str.empty()) return true;
    if(!head && !str.empty()) return false;
    size_t strSize = str.size();
    size_t currentCharCounter = head->count;
    Node* current = head;
    for(size_t i = 0 ; i < strSize ; i++)
    {
        if(currentCharCounter == 0)
        {
            current = current->next;
            if(!current) return false; // if RleString is shorter than the argument
            currentCharCounter = current->count;
        }
        if(str[i] != current->symbol)
            return false;
        
        currentCharCounter--;
    }
   if (current->next || currentCharCounter > 0) return false;

   return true; 
}
size_t RleString::size() const noexcept
{
    return listLength;
}
void RleString::insertAt(size_t index , char value)
{

}
void RleString::removeAt(size_t index)
{
    if(!head) throw std::out_of_range("empty string");
    if(index >= listLength) throw std::out_of_range("invalid index");
    Node* current = head;
    size_t charCounter = head->count;
    Node* previous = head;
    while(index > charCounter - 1)
    {
        charCounter += current->next->count;
        previous = current;
        current = current->next;
    }
    current->count--;
    listLength--;
    
    if(current->count == 0)
    {
        if(current == head)head = head->next;
            else if(current->next) previous->next = current->next;
                else previous->next = nullptr;
        
        delete current;
       
    }


}
void RleString::reverse()
{
    Node* current = head;
    Node* previous = nullptr;
    Node* next = nullptr;
    while (current)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    head = previous;
}
bool RleString::contains(const RleString& rle) const
{
    return false;
}


