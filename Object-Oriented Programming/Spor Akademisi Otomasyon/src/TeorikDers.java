//Leyuza Köksöken
//22100011029

public class TeorikDers extends Ders { //dersin alt sınıfı
    private static int teorikID = 1;
    private int dersID;
    private int dersKredi;
    private String durum;

    
    public TeorikDers(int bolNo, String dersAd, int dersKredi) {
        super(bolNo, dersAd);
        this.dersID = teorikID++;
        this.dersKredi = dersKredi;
        this.durum = "Teorik";
    }

    public int getDersID() {
        return dersID;
    }

    public int getDersKredi() {
        return dersKredi;
    }

    public String getDurum() {
        return durum;
    }
}
