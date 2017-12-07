// /// $Id$


#ifndef PAIVAYS_HH
#define PAIVAYS_HH

class HuonoPaivays
{
  // Tyhjä pelletoteutus poikkeusluokalle, jotta kääntyisi
};

 /*!
 * \version $Id$
 * \file paivays.hh
 * \brief Yksinkertaisen päiväys-luokan esittely
 * \author ©2014 Matti Rintala (matti.rintala@tut.fi)
 **/

 /*!
  * \brief Yksinkertainen päiväysluokka
  **/
class Paivays
{
public:
  
   /*!
   * \brief Rakentaja alustaa päiväyksen annettuun päivämäärään
   * \param p Päivä
   * \param k Kuukausi
   * \param v Vuosi
   * \pre 1 <= p <= kpit(k, v) && 1 <= k <= 12 && v >= 1754
   **/
  Paivays(unsigned int p, unsigned int k, unsigned int v);
  
   /*!
   * \brief Purkaja purkaa päiväyksen
   * \pre -
   **/
  ~Paivays();

   /*!
   * \brief asetaPaiva asettaa päivän
   * \param paiva Uusi päivä
   * \pre 1 <= paiva <= 31
   * \post Päiväyksen päivä on asetettu annetuksi (kuukausi ja vuosi ennallaan)
   * \exception HuonoPaivays   Päivänumero on liian suuri kuukauteen
   */
  void asetaPaiva(unsigned int paiva);

   /*!
   * \brief asetaKk asettaa kuukauden
   * \param kuukausi Uusi kuukausi
   * \pre 1 <= kuukausi <= 12
   * \post Päiväyksen kuukausi on asetettu annetuksi (päivä ja vuosi ennallaan)
   * \exception HuonoPaivays   Päivänumero on liian suuri kuukauteen
   */
  void asetaKk(unsigned int kuukausi);

   /*!
   * \brief asetaVuosi asettaa vuodend
   * \param vuosi Uusi vuosi
   * \pre vuosi >= 1754
   * \post Päiväyksen vuosi on asetettu annetuksi (päivä ja kuukausi ennallaan)
   * \exception HuonoPaivays   Päivänumero on liian suuri kuukauteen
   */
  void asetaVuosi(unsigned int vuosi);

   /*!
   * \brief annaPaiva palauttaa päivän
   * \return Päivämäärän päivä
   * \pre -
   */
  unsigned int annaPaiva() const;

   /*!
   * \brief annaKk palauttaa kuukauden
   * \return Päivämäärän kuukausi
   * \pre -
   */
  unsigned int annaKk() const;

   /*!
   * \brief annaVuosi palauttaa vuoden
   * \return Päivämäärän vuosi
   * \pre -
   */
  unsigned int annaVuosi() const;

   /*!
   * \brief etene siirtää päiväystä eteen/taaksepäin
   * \param n montako päivää siirrytään (negatiivinen = taaksepäin)
   * \pre -
   * \post Päiväystä on siirretty n päivää eteen/taaksepäin
   */
  void etene(int n);

   /*!
   * \brief paljonkoEdella kertoo, montako päivää annettu päiväys on toista edellä
   * \param p Päiväys, jota vertaillaan
   * \return Päiväysten ero päivinä (positiivinen = p myöhemmin, negatiivinen = p aiemmin)
   * \pre -
   */
  int paljonkoEdella(Paivays const& p) const;

  /*!
   * \brief kuukaudenPituus kertoo, mikä on päiväyksessä sillä hetkellä olevan kuukauden pituus
   * \return Päiväyksen kuukauden pituus
   */
  unsigned int kuukaudenPituus() const;

private:
  unsigned int paiva_;    //!< Päivämäärän päivä
  unsigned int kuukausi_; //!< Päivämäärän kuukausi
  unsigned int vuosi_;    //!< Päivämäärän vuosi

  /*!
   * \class Paivays
   * \internal
   * \invariant 1 <= paiva_ <= kuukauden pituus ja 1 <= kuukausi_ <= 12 ja vuosi_ >= 1754
   **/

  /*!
   * \brief invariantti testaa luokkainvariantin
   */
  void invariantti() const;
};

#endif
