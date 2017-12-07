#ifndef MURTOLUKU_HH
#define MURTOLUKU_HH

class Murtoluku
{
public:
  Murtoluku(int osoittaja, int nimittaja);
  ~Murtoluku();

  int annaOsoittaja() const;
  int annaNimittaja() const;
  double annaLiukulukuna() const;

  Murtoluku& operator+=(Murtoluku m);
  Murtoluku& operator/=(Murtoluku m);
// ...

private:
  int osoittaja_;
  int nimittaja_;
};

#endif // MURTOLUKU_HH
