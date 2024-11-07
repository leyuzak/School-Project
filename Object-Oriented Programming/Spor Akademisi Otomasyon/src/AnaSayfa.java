//Leyuza Köksöken,
//22100011029

import java.util.Scanner;

public class AnaSayfa {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); // kullanıcıdan girdi almak için scanner nesnesi oluşturdum.

        System.out.print("Kaç tane bölüm olduğu bilgisini giriniz: ");
        int bolumSayisi = scanner.nextInt(); // bölüm sayısını aldım.
        Bolum[] bolumler = new Bolum[bolumSayisi]; // bölüm dizisini oluşturdum

        // bölümlerin bilgisini alıyoruz
        for (int i = 0; i < bolumSayisi; i++) {
            scanner.nextLine(); // karışıklık olmaması için
            
            System.out.print("Bölümün Nosu: ");
            int bolNo = scanner.nextInt(); 
            
            scanner.nextLine();
            System.out.print("Bölümün Adı: ");
            String bolAd = scanner.nextLine();
            bolumler[i] = new Bolum(bolNo, bolAd); // bölüm nesnesini oluşturduk

            System.out.print("Kaydı alınan bölüm için kaç tane öğrenci olduğu bilgisini girmelisiniz: ");
            int ogrenciSayisi = scanner.nextInt(); 

            bolumler[i].ogrenciler = new Ogrenci[ogrenciSayisi];

            // her öğrencinin bilgisini alıyoruz
            for (int j = 0; j < ogrenciSayisi; j++) {
                scanner.nextLine(); 
                
                System.out.print("Öğrencimizin adı: ");
                String ogrAd = scanner.nextLine(); 
                
                System.out.print("Öğrencimizin soyadı: ");
                String ogrSoyad = scanner.nextLine(); 
                
                System.out.print("Öğrencimizin sınıfı: ");
                int ogrSinif = scanner.nextInt(); 
                
                bolumler[i].ogrenciler[j] = new Ogrenci(bolNo, ogrAd, ogrSoyad, ogrSinif); // öğrenci nesnesi oluşturduk
            }

            System.out.print("Kaç tane teorik ders olduğu bilgisini girmelisiniz: ");
            int teorikDersSayisi = scanner.nextInt();
            // teorik dersler için dizimizi oluşturduk
            bolumler[i].teorikdersler = new TeorikDers[teorikDersSayisi];

            // teorik ders için bilgilerini alıyoruz.
            for (int k = 0; k < teorikDersSayisi; k++) {
                scanner.nextLine(); 

                System.out.print("Ders Adı: ");
                String dersAd = scanner.nextLine(); 
                
                System.out.print("Ders Kredisi: ");
                int dersKredi = scanner.nextInt();
                
                bolumler[i].teorikdersler[k] = new TeorikDers(bolNo, dersAd, dersKredi); // teorik ders nesnesi oluşturuyoruz.
            }

            System.out.print("Kaç tane pratik ders olduğu bilgisini girmelisiniz: ");
            int pratikDersSayisi = scanner.nextInt();

            bolumler[i].pratikdersler = new PratikDers[pratikDersSayisi];
            
            // pratik derslerin bilgilerini kullanıcıdan alıyoruz
            for (int l = 0; l < pratikDersSayisi; l++) {
                scanner.nextLine(); 

                System.out.print("Ders Adı: ");
                String dersAd = scanner.nextLine();
                
                System.out.print("Ders Kredisi: ");
                int dersKredi = scanner.nextInt(); 

                bolumler[i].pratikdersler[l] = new PratikDers(bolNo, dersAd, dersKredi); // pratik ders nesnesi yaptık
            }
        }
        
        int secim; // kullanıcı altıya basana kadar menü gösterilir.
        do {
            System.out.println(" ****************-MENÜ-**************** ");
            System.out.println("1) Tüm bölümlerin bilgilerini listelemek için:");
            System.out.println("2) Öğrencileri listelemek için:");
            System.out.println("3) Teorik dersleri listelemek için:");
            System.out.println("4) Pratik dersleri listelemek için:");
            System.out.println("5) Arama yapmak için:");
            System.out.println("6) Çıkmak için:");
            System.out.println(" ******************************** ");
            System.out.print("Seçiminizi yapın: ");
            secim = scanner.nextInt();
            
            switch (secim) {
                case 1:
                    listeleBolumler(bolumler);
                    break;
                case 2:
                    listeleOgrenciler(bolumler);
                    break;
                case 3:
                    listeleTeorikDersler(bolumler);
                    break;
                case 4:
                    listelePratikDersler(bolumler);
                    break;
                case 5:
                    aramaYap(bolumler);
                    break;
                case 6:
                    System.out.println("Program sonlandırıldı."); 
                    break;
                default:
                    System.out.println("Geçersiz seçim, lütfen tekrardan deneyin."); 
            }
        } while (secim != 6);

        scanner.close();
    }

            
    public static void listeleBolumler(Bolum[] bolumler) { //main sayfasında olduğumuzdan ve onu kullandığımızdan static
        System.out.println("Tüm Bölümler: "); 
        for (Bolum bolum : bolumler) {
            System.out.println("Bölüm numarası: " + bolum.getBolNo() + ", Bölümün adı: " + bolum.getBolAd());
        }
    }

    public static void listeleOgrenciler(Bolum[] bolumler) {
        System.out.println("Tüm Öğrenciler: "); 
        for (Bolum bolum : bolumler) {
            for (Ogrenci ogrenci : bolum.getOgrenciler()) {
                System.out.println("Oğrenci numarası: " + ogrenci.getOgrID() + ", Ogrenci adı: " + ogrenci.getOgrAd() + ", Ogrenci soyadı: " + ogrenci.getOgrSoyad() + ", Ogrencinin sınıfı: " + ogrenci.getOgrSinif()); // Her öğrencinin bilgilerini yazdırıyoruz.
            }
        }
    }
    public static void listeleTeorikDersler(Bolum[] bolumler) {
        System.out.println("Tüm Teorik Dersler :");
        for (Bolum bolum : bolumler) {
            for (Ders ders : bolum.getTeorikdersler()) {
                if (ders instanceof TeorikDers) {
                    TeorikDers teorikDers = (TeorikDers) ders; 
                    //instanceof ile teorik nesnesi ders sinifina ait mi deil mi diye kontrol ederiz
                    System.out.println("Ders ID: " + teorikDers.getDersID() + 
                                       ", Dersin adı: " + teorikDers.getDersAd() + 
                                       ", Kredisi: " + teorikDers.getDersKredi()); 
                }
            }
        }
    }


    public static void listelePratikDersler(Bolum[] bolumler) {
        System.out.println("Tüm Pratik Dersler:"); 
        for (Bolum bolum : bolumler) {
            for (Ders ders : bolum.getPratikdersler()) {
                if (ders instanceof PratikDers) { 
                    PratikDers pratikDers = (PratikDers) ders; 
                    System.out.println("Ders ID: " + pratikDers.getDersID() + 
                    		           ", Ders Adı: " + pratikDers.getDersAd() + 
                                       ", Kredisi: " + pratikDers.getDersKredi()); 
                }
            }
        }
    }



    public static void aramaYap(Bolum[] bolumler) {
        Scanner scanner = new Scanner(System.in); 

        System.out.print("Aramak istediğiniz kelimeyi girin: "); 
        String aranacakKelime = scanner.nextLine(); 

        boolean bulundu = false; // öğrenci ya da dersi bulduk mu diye

       //ogrenci arama methodu
        for (Bolum bolum : bolumler) { 
            for (Ogrenci ogrenci : bolum.getOgrenciler()) { 
                if (ogrenci != null && (ogrenci.getOgrAd().contains(aranacakKelime) || ogrenci.getOgrSoyad().contains(aranacakKelime))) { 
                	// ogrenci adı ya da soyadının aranını içerdiğine dair & ile kontrol
                    bulundu = true; // Öğrenci bulundu.
                    System.out.println("Öğrenci bulundu: " + ogrenci.getOgrAd() + " " + ogrenci.getOgrSoyad() + " - Bölüm: " + bolum.getBolAd());
                }
            }
        }

        // dersi arama 
        for (Bolum bolum : bolumler) { 
            for (TeorikDers ders : bolum.getTeorikdersler()) { //teorik dersleri kontrol
                if (ders != null && ders.getDersAd().contains(aranacakKelime)) { 
                    //constains metodu ile arama islemi yaptım.
                    bulundu = true; // bulduk
                    System.out.println("Ders bulundu: " + ders.getDersAd() + " - Bölüm: " + bolum.getBolAd()); 
                }
            }

            for (PratikDers ders : bolum.getPratikdersler()) { // pratik dersleri kontrol 
                if (ders != null && ders.getDersAd().contains(aranacakKelime)) { 
                    bulundu = true; // bulduk
                    System.out.println("Ders bulundu: " + ders.getDersAd() + " - Bölüm: " + bolum.getBolAd()); 
                }
            }
        }

        if (!bulundu) { // eger ders veya öğrenci bulunmadıysa
            System.out.println("Öğrenci veya ders bulunamadı."); // kullanıcıya geri mesaj

    }
}
}