//Leyuza Köksöken
//22100011029

public class PratikDers extends Ders { //dersin alt sınıfı encapsulation 
    private static int pratikID = 1;
    private int dersID;
    private int dersKredi;
    private String durum;


    public PratikDers(int bolNo, String dersAd, int dersKredi) {
        super(bolNo, dersAd); //ust sınıftan almak için bilgileri
        this.dersID = pratikID++;
        this.dersKredi = dersKredi;
        this.durum = "Pratik";
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
