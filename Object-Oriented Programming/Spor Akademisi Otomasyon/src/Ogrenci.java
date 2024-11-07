//Leyuza Köksöken
//22100011029


public class Ogrenci {
    private static int ogrIDsayacı = 1;
    private int ogrID;
    private int bolNo;
    private String ogrAd;
    private String ogrSoyad;
    private int ogrSinif;

    public Ogrenci(int bolNo, String ogrAd, String ogrSoyad, int ogrSinif) {
        this.ogrID = ogrIDsayacı++; //ogrID, her öğrenci oluşturulduğunda otomatik olarak arttırılacak kısmı
        this.bolNo = bolNo;
        this.ogrAd = ogrAd;
        this.ogrSoyad = ogrSoyad;
        this.ogrSinif = ogrSinif;
    }

    public int getOgrID() {
        return ogrID;
    }

    public int getBolNo() {
        return bolNo;
    }

    public String getOgrAd() {
        return ogrAd;
    }

    public String getOgrSoyad() {
        return ogrSoyad;
    }

    public int getOgrSinif() {
        return ogrSinif;
    }

    @Override //üzerine yazma
    public String toString() {
        return "Öğrenci ID: " + ogrID +
               ", Bölüm No: " + bolNo +
               ", Ad: " + ogrAd +
               ", Soyad: " + ogrSoyad +
               ", Sınıf: " + ogrSinif;
    }
}
