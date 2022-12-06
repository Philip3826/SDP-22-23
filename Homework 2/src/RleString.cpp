#include "RleString.h"
#include<stdexcept>

// TODO Write your implementation here
void RleString::Node::insertAfter(Node*& newNode)
{
    if(!this->next) this->next = newNode;
        else
        {
            newNode->next = this->next;
            this->next = newNode;
        }
    
}
void RleString::Node::removeNext()
{
    if (this->next)
    {
        if(this->next->next)
        {
            Node* toDelete = this->next;
            this->next = toDelete->next;
            delete toDelete;
        }
        else
        {
            delete this->next;
            this->next = nullptr;
        }
    }
}
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
            stringLength += LastNode->count;
            LastNode->next = newNode;
            LastNode = LastNode->next;
        }
        LastNode->count++;
    }
    stringLength += LastNode->count;
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
    this->stringLength = other.stringLength;
}
void RleString::free()
{
    while(head)
    {
        Node* current = head;
        head = head->next;
        delete current;
    }
    stringLength = 0;
}
// public
RleString::RleString() : head(nullptr) , stringLength(0)
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
    return stringLength;
}
void RleString::insertAt(size_t index , char value)
{   
    if(index > stringLength) throw std::out_of_range("invalid index");
    if(!head) 
    {
        head = new Node(value,1);
        stringLength++;
        return;
    }
    
    if(index >= 0 && index <= head->count)
    {
        if (value == head->symbol) head->count++;
        else  if( head->next && value == head->next->symbol && index == head->count) head->next->count++; // if we have "aaabb" and we want to add b at position 4 , we increment the next node
        else 
        {
            Node* newNode = new Node(value,1);
            if (index == 0)
            {
               newNode->insertAfter(head);
               head = newNode;
            }
            else if (index == head->count) head->insertAfter(newNode);
            else // we have to split the head Node in two
            {
                Node* splitNode = new Node(head->symbol,head->count - index);
                head->count = index;
                head->insertAfter(splitNode); // head -> splitNode -> ....
                head->insertAfter(newNode); // head -> newNode -> splitNode -> ....
            }
        }
        
    }
    else
    {
       Node* current = head->next;
       size_t charCounter = head->count + current->count;
       Node* previous = head;

       while (current->next && index > charCounter)
       {
            charCounter+= current->next->count;
            previous = current;
            current = current->next;
       }

       if(value == current->symbol) current->count++;
       else
       {
            Node* newNode = new Node(value,1);
            if( current->next && value ==  current->next->symbol && index == charCounter) current->next->count++;
            else
            {
                if (index == charCounter - current->count) previous->insertAfter(newNode);
                
                if(index == charCounter) current->insertAfter(newNode);
                else
                {
                    Node* splitNode = new Node (current->symbol,charCounter - index);
                    current->count -= splitNode->count;
                    current->insertAfter(splitNode); // ... -> current -> splitNode ->....
                    current->insertAfter(newNode);// ... -> current -> newNode -> splitNode -> .....
                }
            }
       }
        
    }
    stringLength++;
}

void RleString::removeAt(size_t index)
{
    if(!head) throw std::out_of_range("empty string");
    if(index >= stringLength) throw std::out_of_range("invalid index");
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
    stringLength--;
    
    if(current->count == 0)
    {
        if(current == head)
        {
            current = current->next;
            delete head;
            head = current;
        }
        else previous->removeNext();
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
    if(!rle.head) return true; // "" is a substring of every string
    if(!this->head) return false; // "" has no substrings except ""

    if(rle.stringLength > this->stringLength) return false; // substring must be shorter than the string
   
   Node* current = head;
   Node* subCurrent = rle.head;

   while (current && subCurrent)
   {
        if(current->symbol == subCurrent->symbol)
        {
            if(subCurrent == rle.head || !subCurrent->next) 
            {
                if(current->count >= subCurrent->count) subCurrent = subCurrent->next;
            }
            else
            {
                if(current->count == subCurrent->count) subCurrent = subCurrent->next;
            }
        }
        else
        {
            subCurrent = rle.head;
        }
     current = current->next;
   }
   
   if(!subCurrent) return true;

   return false;

}


