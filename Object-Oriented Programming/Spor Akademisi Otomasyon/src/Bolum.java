//Leyuza Köksöken
//22100011029


public class Bolum {
    private int bolNo;
    private String bolAd;
    public Ogrenci[] ogrenciler;
    public TeorikDers[] teorikdersler;
    public PratikDers[] pratikdersler;

    public Bolum(int bolNo, String bolAd) {
        this.bolNo = bolNo;
        this.bolAd = bolAd;
    }

    public int getBolNo() {
        return bolNo;
    }

    public String getBolAd() {
        return bolAd;
    }

    public void setOgrenciler(Ogrenci[] ogrenciler) {
        this.ogrenciler = ogrenciler;
    }

    public void setTeorikdersler(TeorikDers[] teorikdersler) {
        this.teorikdersler = teorikdersler;
    }

    public void setPratikdersler(PratikDers[] pratikdersler) {
        this.pratikdersler = pratikdersler;
    }

    public Ogrenci[] getOgrenciler() {
        return ogrenciler; 
    }

    public TeorikDers[] getTeorikdersler() {
        return teorikdersler; 
    }

    public PratikDers[] getPratikdersler() {
        return pratikdersler; 
    }
}
