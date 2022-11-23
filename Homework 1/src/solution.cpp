#include "solution.h"
#include <stack>
bool isCorrect(const char* expression)
{
  std::stack<char> st;
  size_t i = 0;

  while (expression[i])
  {
      switch(expression[i])
      {
        case '(' : st.push(expression[i]);break;
        case '{' : st.push(expression[i]);break;
        case '[' : st.push(expression[i]);break;
        case ')' :
        {
          if (!st.empty() && st.top() == '(') st.pop();
           else return false;
        } break;
        case '}':
        {
          if (!st.empty() && st.top() == '{') st.pop();
           else return false;
        }break;
        case ']':
        {
          if(!st.empty() && st.top() == '[') st.pop();
           else return false;
        }break;
        //default: continue;
      }
      i++;
  }
  if(st.empty()) return true;
   else return false;
}