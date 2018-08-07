/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author Star Lord
 */
public class Produs {

    private String denumire, categorie, taraOrigine;
    private double pret;

    public Produs() {
    }

    public Produs(String denumire, String categorie, String taraOrigine, double pret) {
        this.denumire = denumire;
        this.categorie = categorie;
        this.taraOrigine = taraOrigine;
        this.pret = pret;
    }

    public void setDenumire(String numeNou) {
        denumire = numeNou;
    }

    public String getDenumire() {
        return denumire;
    }

    public void setCategorie(String categorieNoua) {
        categorie = categorieNoua;
    }

    public String getCategorie() {
        return categorie;
    }

    public void setTaraOrigine(String taraNoua) {
        taraOrigine = taraNoua;
    }

    public String getTaraOrigine() {
        return taraOrigine;
    }

    public void setPret(double pretNou) {
        pret = pretNou;
    }

    public double getPret() {
        return pret;
    }

    public String toString() {
        String s = new String();
        return s + "" + denumire + " " + categorie + " " + taraOrigine + " " + pret;

    }

    public static void main(String[] args) {
        Produs p = new Produs();
        Scanner scan = null;

        try {
            scan = new Scanner(new File("produse.txt"));
        } catch (Exception e) {
            System.out.println("produse.txt not found");
        }

        List<Produs> produse = new ArrayList<Produs>();
        int contor;
        String line = scan.nextLine();
        String[] tari = line.split(" ");
        int len = tari.length - 2;

        while (scan.hasNextLine()) {
            line = scan.nextLine();
            String[] details = line.split(" ");
            for (contor = 0; contor < len; contor++) {
                p.denumire = details[0];
                p.taraOrigine = tari[contor + 2];
                p.categorie = details[1];
                p.pret = Double.parseDouble(details[contor + 2]);
                Produs pp = new Produs(p.denumire, p.categorie, p.taraOrigine, p.pret);
                produse.add(pp);
            }
        }

        scan.close();

        for (int i = 0; i < produse.size(); i++) {
            System.out.println(produse.get(i));

        }
    }
}
    
