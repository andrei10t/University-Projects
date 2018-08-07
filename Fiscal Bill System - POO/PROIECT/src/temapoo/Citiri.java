/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;


import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Vector;

/**
 *
 * @author Star Lord
 */
public class Citiri {

    public Vector<String> citireCategorie() {
        Scanner scanCategorie = null;
        try {
            scanCategorie = new Scanner(new File("produse.txt"));
        } catch (Exception e) {
            System.out.println("produse.txt not found");
            e.printStackTrace();
        }
        String line = scanCategorie.nextLine();
        Vector<String> categorii = new Vector<String>();
        while (scanCategorie.hasNext()) {
            line = scanCategorie.nextLine();
            String[] details = line.split(" ");
            categorii.add(details[0]);
        }
        return categorii;
    }

    public Vector<String> citireTari() {
        Scanner scanTari = null;
        try {
            scanTari = new Scanner(new File("produse.txt"));
        } catch (Exception e) {
            System.out.println("produse.txt not found");
            e.printStackTrace();
        }
        Vector<String> tari=new Vector<String>();
        String line = scanTari.nextLine();
        String[] t = line.split(" ");   //vezi ca sari tari[0];
        for(String tara:t){
            tari.add(tara);
        }
        tari.remove(0);
        tari.remove(0);
        return tari;
    }

    public List<Produs> citireProduse() {
        Scanner scanProduse = null;

        Produs p = new Produs();

        try {
            scanProduse = new Scanner(new File("produse.txt"));
        } catch (Exception e) {
            System.out.println("produse.txt not found");
            e.printStackTrace();
        }

        List<Produs> produse = new ArrayList<Produs>();
        int contor;
        String line = scanProduse.nextLine();
        String[] tari = line.split(" ");
        int len = tari.length - 2;

        while (scanProduse.hasNextLine()) {
            line = scanProduse.nextLine();
            String[] details = line.split(" ");
            for (contor = 0; contor < len; contor++) {
                p.setDenumire(details[0]);
                p.setTaraOrigine(tari[contor + 2]);
                p.setCategorie(details[1]);
                p.setPret(Double.parseDouble(details[contor + 2]));
                Produs pp = new Produs(p.getDenumire(), p.getCategorie(), p.getTaraOrigine(), p.getPret());
                produse.add(pp);
            }
        }
        /* for (int i = 0; i < produse.size(); i++) {
         System.out.println(produse.get(i));
         } */

        scanProduse.close();
        return produse;
    }

    public Factura citireProduseComandate() {
        Scanner scanFacturi = null;
        Produs p = new Produs();
        String line;
        Map<String, Map<String, Integer>> taxe = citireTaxe();

        try {
            scanFacturi = new Scanner(new File("facturi.txt"));
        } catch (Exception e) {
            System.out.println("facturi.txt not found");
            e.printStackTrace();
        }

        Factura produseComandate = new Factura();

        List<Produs> produse = citireProduse();

        while (scanFacturi.hasNextLine()) {
            line = scanFacturi.nextLine();

            if (line.contains("Magazin")) {
                scanFacturi.nextLine();
                scanFacturi.nextLine();
                scanFacturi.nextLine();
            }
            if (line.contains("Factura")) {
                scanFacturi.nextLine();
            }
            line = scanFacturi.nextLine();
            while (line.length() != 0 && scanFacturi.hasNextLine()) {
                String[] details = line.split(" ");
                p = new Produs();
                p.setDenumire(details[0]);
                p.setTaraOrigine(details[1]);
                for (Produs pnou : produse) {
                    if (p.getDenumire().equals(pnou.getDenumire()) && p.getTaraOrigine().equals(pnou.getTaraOrigine())) {
                        p.setCategorie(pnou.getCategorie());
                        p.setPret(pnou.getPret());
                        break;
                    }

                }
                int taxaCurenta = taxe.get(p.getTaraOrigine()).get(p.getCategorie());
                ProdusComandat pc = new ProdusComandat(p, taxaCurenta, Integer.parseInt(details[2]));
                produseComandate.factura.add(pc);

                line = scanFacturi.nextLine();

                if (!scanFacturi.hasNextLine()) {
                    String[] detail = line.split(" ");
                    Produs pp = new Produs();
                    pp.setDenumire(detail[0]);
                    pp.setTaraOrigine(detail[1]);
                    for (Produs pnou : produse) {
                        if (pp.getDenumire().equals(pnou.getDenumire()) && pp.getTaraOrigine().equals(pnou.getTaraOrigine())) {
                            pp.setCategorie(pnou.getCategorie());
                            pp.setPret(pnou.getPret());
                            break;
                        }

                    }
                    taxaCurenta = taxe.get(pp.getTaraOrigine()).get(pp.getCategorie());
                    ProdusComandat ppc = new ProdusComandat(pp, taxaCurenta, Integer.parseInt(details[2]));
                    produseComandate.factura.add(ppc);
                }
            }
        }
        scanFacturi.close();

        return produseComandate;
    }

    public List<Magazin> citireMagazinFacturi() {
        Scanner scanFacturi = null;
        List<Magazin> magazine = new ArrayList<Magazin>();
        Produs p = new Produs();
        Map<String, Map<String, Integer>> taxe = citireTaxe();
        Vector<Factura> magazinCurent;
        magazinCurent = new Vector<Factura>();
        Magazin m = null;
        Factura facturaCurenta;
        facturaCurenta = new Factura();
        
        String line;
        try {
            scanFacturi = new Scanner(new File("facturi.txt"));
        } catch (Exception e) {
            System.out.println("facturi.txt not found");
            e.printStackTrace();
        }

        List<Produs> produse = citireProduse();

        while (scanFacturi.hasNextLine()) {
            line = scanFacturi.nextLine();
            if (line.contains("Magazin")) {              // am un magazin nou
                String[] numeMagazin = line.split(":");
                if (line.contains("MiniMarket")) {
                    m = MagazinFactory.buildMagazin(MagazinType.MINI);
                }
                if (line.contains("MediumMarket")) {
                    m = MagazinFactory.buildMagazin(MagazinType.MEDIUM);
                }
                if (line.contains("HyperMarket")) {
                    m = MagazinFactory.buildMagazin(MagazinType.HYPER);
                }
                
                                        //il adaug

                magazinCurent = new Vector<Factura>();   //ii fac o factura
                m.magazin = magazinCurent; 
                m.nume=numeMagazin[2];
                magazine.add(m);
                
//il adaug
                scanFacturi.nextLine();
                line = scanFacturi.nextLine();

                if (line.contains("Factura")) {
                    facturaCurenta.denumire = line;      //nume factura
                    scanFacturi.nextLine();

                }

                line = scanFacturi.nextLine();
                while (line.length() != 0 && scanFacturi.hasNextLine()) {
                    String[] details = line.split(" ");
                    p = new Produs();
                    p.setDenumire(details[0]);
                    p.setTaraOrigine(details[1]);
                    for (Produs pnou : produse) {     //setez categorie si tara
                        if (p.getDenumire().equals(pnou.getDenumire()) && p.getTaraOrigine().equals(pnou.getTaraOrigine())) {
                            p.setCategorie(pnou.getCategorie());
                            p.setPret(pnou.getPret());
                            break;
                        }

                    }
                    int taxaCurenta = taxe.get(p.getTaraOrigine()).get(p.getCategorie());
                    ProdusComandat pc = new ProdusComandat(p, taxaCurenta, Integer.parseInt(details[2]));

                    facturaCurenta.factura.add(pc);       //pun produsul comandat pe factura
                    line = scanFacturi.nextLine();
                    if (!scanFacturi.hasNextLine()) {
                        String[] detail = line.split(" ");
                        Produs pp = new Produs();
                        pp.setDenumire(detail[0]);
                        pp.setTaraOrigine(detail[1]);
                        for (Produs pnou : produse) {
                            if (pp.getDenumire().equals(pnou.getDenumire()) && pp.getTaraOrigine().equals(pnou.getTaraOrigine())) {
                                pp.setCategorie(pnou.getCategorie());
                                pp.setPret(pnou.getPret());
                                break;
                            }

                        }
                        taxaCurenta = taxe.get(pp.getTaraOrigine()).get(pp.getCategorie());
                        ProdusComandat pcc = new ProdusComandat(pp, taxaCurenta, Integer.parseInt(details[2]));

                        facturaCurenta.factura.add(pcc);
                    }
                }
                magazinCurent.add(facturaCurenta);
                facturaCurenta = new Factura();
            } else {
                if (line.contains("Factura")) {
                    scanFacturi.nextLine();
                }

                line = scanFacturi.nextLine();

                while (line.length() != 0 && scanFacturi.hasNextLine()) {
                    String[] details = line.split(" ");
                    p = new Produs();
                    p.setDenumire(details[0]);
                    p.setTaraOrigine(details[1]);

                    line = scanFacturi.nextLine();
                    for (Produs pnou : produse) {
                        if (p.getDenumire().equals(pnou.getDenumire()) && p.getTaraOrigine().equals(pnou.getTaraOrigine())) {
                            p.setCategorie(pnou.getCategorie());
                            p.setPret(pnou.getPret());
                            break;
                        }

                    }
                    int taxaCurenta = taxe.get(p.getTaraOrigine()).get(p.getCategorie());
                    ProdusComandat pc = new ProdusComandat(p, taxaCurenta, Integer.parseInt(details[2]));
                    facturaCurenta.factura.add(pc);
                    if (!scanFacturi.hasNextLine()) {
                        String[] detail = line.split(" ");
                        Produs pp = new Produs();
                        pp.setDenumire(detail[0]);
                        pp.setTaraOrigine(detail[1]);

                        for (Produs pnou : produse) {
                            if (pp.getDenumire().equals(pnou.getDenumire()) && pp.getTaraOrigine().equals(pnou.getTaraOrigine())) {
                                pp.setCategorie(pnou.getCategorie());
                                pp.setPret(pnou.getPret());
                                break;
                            }

                        }
                        taxaCurenta = taxe.get(pp.getTaraOrigine()).get(pp.getCategorie());
                        ProdusComandat pcc = new ProdusComandat(pp, taxaCurenta, Integer.parseInt(details[2]));
                        facturaCurenta.factura.add(pcc);
                    }
                }
                magazinCurent.add(facturaCurenta);
                facturaCurenta = new Factura();
            }
        }
        m.magazin = magazinCurent;
        magazine.add(m);

        scanFacturi.close();
        magazine.remove(magazine.size()-1) ;
        return magazine;
    }

    public Map<String, Map<String, Integer>> citireTaxe() {
        Scanner scanTaxe = null;

        try {
            scanTaxe = new Scanner(new File("taxe.txt"));
        } catch (Exception e) {
            System.out.println("taxe.txt not found");
            e.printStackTrace();
        }

        Map<String, Map<String, Integer>> taxe = new HashMap<String, Map<String, Integer>>();

        String line = scanTaxe.nextLine();
        String[] tari = line.split(" ");
        int len = tari.length;

        while (scanTaxe.hasNext()) {

            line = scanTaxe.nextLine();
            String[] details = line.split(" ");
            for (int j = 1; j < len; j++) {
                if (!taxe.containsKey(tari[j])) {
                    taxe.put(tari[j], new HashMap<String, Integer>());
                }
                Map<String, Integer> categorieProcent = taxe.get(tari[j]);
                categorieProcent.put(details[0], Integer.parseInt(details[j]));
                taxe.put(tari[j], categorieProcent);
            }
        }

        return taxe;
    }

    public static void main(String[] args) {
        Citiri citire = new Citiri();
        /*
         List<Produs> produse = citire.citireProduse();
         for (int i = 0; i < produse.size(); i++) {
         System.out.println(produse.get(i));
         }
         *//*
         System.out.println();

         Factura pc = citire.citireProduseComandate();
         for (ProdusComandat p:pc.factura) {
         System.out.println(p);
         }
         System.out.println();
         */

        List<Magazin> mf = citire.citireMagazinFacturi();
        
        //for (int i=0;i<1;i++) {
            System.out.println(mf.get(0));
            System.out.println(mf.get(1));
            System.out.println(mf.get(2));
            System.out.println(mf.get(3));
           
         
        //}
    }
}

/*
 Map<String, Map<String, Integer>> taxe = new HashMap<String, Map<String, Integer>>();
 taxe = citire.citireTaxe();
 System.out.println(taxe);
 */
