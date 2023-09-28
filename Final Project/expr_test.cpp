#include <iostream>
#include <cmath>
#include "expr.h"
#include "expr_parser.h"
#include "func.h"
#include <sstream>

using std::cout;
using std::endl;

#ifndef ASSERT
#include <csignal>  // signal handler 
#include <cstring>  // memset
#include <string>
char programName[128];

void segFaultHandler(int, siginfo_t*, void* context) {
  char cmdbuffer[1024];
  char resultbuffer[128];
#ifdef __APPLE__
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext->__ss.__rip);
#else
  sprintf(cmdbuffer, "addr2line -Cfip -e %s %p", programName,
      (void*)((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP]);
#endif
  std::string result = "";
  FILE* pipe = popen(cmdbuffer, "r");
  if (!pipe) throw std::runtime_error("popen() failed!");
  try {
    while (fgets(resultbuffer, sizeof resultbuffer, pipe) != NULL) {
      result += resultbuffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  cout << "Segmentation fault occured in " << result;
#ifdef __APPLE__
  ((ucontext_t*)context)->uc_mcontext->__ss.__rip += 2;  // skip the seg fault
#else
  ((ucontext_t*)context)->uc_mcontext.gregs[REG_RIP] += 2;  // skip the seg fault
#endif
}

#define ASSERT(cond) if (!(cond)) { \
    cout << "failed ASSERT " << #cond << " at line " << __LINE__ << endl; \
  } else { \
    cout << __func__ << " - (" << #cond << ")" << " passed!" << endl; \
  }
#endif



struct expr_test{
static void testVar(){
  Variable* n = new Variable();
  ASSERT(n->left == nullptr);
  ASSERT(n->right == nullptr);
  ASSERT(n->val == 0.0);
  ASSERT(n->eval(30) == 30);

  delete n;
}

static void test1op(){
  Variable* a = new Variable();
  ASSERT(a->left == nullptr && a->get_left() == nullptr);
  ASSERT(a->right == nullptr && a->get_right() == nullptr);
  ASSERT(a->val == 0.0);
  ASSERT(a->eval(30) == 30);

  Sin* s = new Sin(a);
  ASSERT(s->left == a && s->get_left() == a);
  ASSERT(s->right == nullptr && s->get_right() == nullptr);
  ASSERT(s->val == 0.0);
  ASSERT(s->eval(1) != 0);
  cout << s->eval(1) <<endl;

  delete s;
}

static void test2op(){
  Expr* a = new Variable();
  ASSERT(a->left == nullptr);
  ASSERT(a->right == nullptr);
  ASSERT(a->val == 0.0);
  ASSERT(a->eval(30) == 30);

  Expr* s = new Sin(a);
  ASSERT(s->left == a);
  ASSERT(s->right == nullptr);
  ASSERT(s->val == 0.0);
  ASSERT(s->eval(1) != 0);
  cout << s->eval(1) <<endl;

  Expr* b = new Variable();

  Expr* plus = new Plus(a, b);  //b cannot be a or seg fault
  ASSERT(plus->left == a);
  ASSERT(plus->right == b);
  ASSERT(plus->val == 0.0);
  ASSERT(plus->eval(1) != 0);
  cout << plus->eval(1) <<endl;

  delete plus;
}

static void splitDeqTest(){
  ExprParser* parser;
  std::deque<std::string> tokens;
  for(int i = 0; i < 10; i++){
    tokens.push_back(std::to_string(i));
  }
  std::deque<std::string> new_d = parser->ExprParser::splitDeque(0, 5, tokens);
  for(size_t i = 0; i < new_d.size(); i++){
    ASSERT(new_d.at(i) == std::to_string(i));
  }
}

static void parseTest(){
  std::istringstream base1("( + ( sin ( * 1.33 x ) ) ( * 0.25 ( cos ( * 6.7 x ) ) ) )");
  ExprParser* parser1 = new ExprParser();
  parser1->top_node = parser1->parse(base1);
  ASSERT(fabs(parser1->top_node->eval(3.1415) + 1.0075) < 0.05);
  delete parser1;

  std::istringstream base3("( * ( cos ( * 6.7 x ) )  0.25 )");
  ExprParser* parser3 = new ExprParser();
  parser3->top_node = parser3->parse(base3);
  ASSERT(fabs(parser3->top_node->eval(3.1415) + 0.14694) < 0.05);
  delete parser3;

  std::istringstream base2("* pi ( sin ( * ( * 2 pi x ) ) )");
  ExprParser* parser2 = new ExprParser();
  parser2->top_node = parser2->parse(base2);
  ASSERT(fabs(parser2->top_node->eval(0.25)-3.141592) < 0.005);
  for(double i = 0; i < 20; i++){
    cout << i << " " << parser2->top_node->eval(i/4) << endl;
  }
  delete parser2;

  std::istringstream base4(" * ( ( ( ) ( x ) ( x ) ( x ) ) )");
  ExprParser* parser4 = new ExprParser();
  parser4->top_node = parser4->parse(base4);
  ASSERT(fabs(parser4->top_node->eval(1.5) ) == 3.375);
  cout << fabs(parser4->top_node->eval(1.5)) << endl;
  delete parser4;

}

static void funcConstructorTest(){
  //copied form testParse
  std::istringstream base1("( + ( sin ( * 1.33 x ) ) ( * 0.25 ( cos ( * 6.7 x ) ) ) )");
  ExprParser* parser = new ExprParser();
  parser->top_node = parser->parse(base1);
  ASSERT(parser->top_node->eval(3.1415) - 1.0075 < 0.005);

  Function* f = new Function("fun 1", parser->top_node);
  ASSERT(f->m_name == "fun 1");
  ASSERT(f->eval(3.1415) - 1.0075 < 0.005);

  delete parser;
  delete f;
}

static void exceptionTest(){

  std::stringstream ss("1 2 3 4 5 6 7");
  std::string temp;
  for(size_t i = 0; i < 10; i++){
    ss >> temp;
    cout << temp << endl;
  }

  std::istringstream base5("( sin x )");
  ExprParser* parser5 = new ExprParser();
  parser5->top_node = parser5->parse(base5);
  for(double i = 0; i < 640; i++){
    double x_val = (i/640)*(10);
    cout << x_val << " " << parser5->top_node->eval(x_val) << endl;
  }
  cout << fabs(parser5->top_node->eval(0)) << endl;
  delete parser5;
}

};

int main(int, char* argv[]){
  cout << "Testing expr" << endl;
  sprintf(programName, "%s", argv[0]);
  struct sigaction signalAction;
  memset(&signalAction, 0, sizeof(struct sigaction));
  signalAction.sa_flags = SA_SIGINFO;
  signalAction.sa_sigaction = segFaultHandler;
  sigaction(SIGSEGV, &signalAction, NULL);

  //expr tests
  expr_test::testVar();
  expr_test::test1op();
  expr_test::test2op();

  //expr_parser tests
  expr_test::splitDeqTest();
  expr_test::parseTest();

  //func tests
  expr_test::funcConstructorTest();

  //exception test
  expr_test::exceptionTest();
  return 0;
}