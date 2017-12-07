#ifndef STRING_HH
#define STRING_HH

#include <vector>

class String
{
public:
  String();
  ~String();

  int length() const;

  void clear();

  String substr(int paikka, int maara) const;

private:
  std::vector<char> merkit_; // Oikeasti toteutettaisiin muuten, esim. char* merkit_;
  int pituus_;               // Pidetään kirjaa merkkien määrästä tehokkuussyistä
};

#endif // STRING_HH
