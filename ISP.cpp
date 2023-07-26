#include <iostream>
#include <vector>

using namespace std;

struct Document 
{
  // nothing inside, just for example
};


//struct IMachine
//{
//  virtual void print(Document& doc) = 0;
//  virtual void fax(Document& doc) = 0;
//  virtual void scan(Document& doc) = 0;
//};
//
//struct MFP : IMachine
//{
//  void print(Document& doc) override;
//  void fax(Document& doc) override;
//  void scan(Document& doc) override;
//};

// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

struct IPrinter
{
  virtual void print(Document& doc) = 0;
};

struct IScanner
{
  virtual void scan(Document& doc) = 0;
};

struct Printer : IPrinter
{
  void print(Document& doc) override { cout << "printing... " << endl;}
};

struct Scanner : IScanner
{
  void scan(Document& doc) override { cout << "scaning... " << endl;}
};

struct IMachine: IPrinter, IScanner
{
};

struct Machine : IMachine
{
  IPrinter& printer;
  IScanner& scanner;

  Machine(IPrinter& printer, IScanner& scanner)
    : printer{printer},
      scanner{scanner}
  {
  }

  void print(Document& doc) override {
    printer.print(doc);
  }
  void scan(Document& doc) override {
    scanner.scan(doc);
  }
};

int main()
{
  Printer l_printer;
  Scanner l_scanner;
  Machine l_machine(l_printer, l_scanner);
  Document l_dummy_doc;
  l_machine.print(l_dummy_doc);
  l_machine.scan(l_dummy_doc);
  return 0;
}