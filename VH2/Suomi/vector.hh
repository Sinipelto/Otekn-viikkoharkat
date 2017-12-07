#ifndef VECTOR_HH
#define VECTOR_HH

class VectorInt
{
public:
  VectorInt();
  ~VectorInt();

  int front() const;

  int& operator[](int paikka);
  int& at(int paikka);

  void push_back(int alkio);

  void swap(VectorInt& vektori);

private:
  int* datalohko_; // Tämän osoittimen päähän tulee new'llä luotu taulukko kokonaislukuja
  int lohkokoko_;  // Varatun taulukon koko
  int alkiolkm_;   // Taulukosta käytetyn osan koko
};

#endif // VECTOR_HH
