/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

import java.util.Vector;

/**
 *
 * @author Star Lord
 */
public abstract class Magazin implements IMagazin {

    public Vector<Factura> magazin;
    public String nume;

    public double getTotalCategorie(String categorie) {
        double rezultat = 0;
        for (Factura f : magazin) {
            rezultat += f.getTotalCategorie(categorie);
        }
        return rezultat;
    }

    public Magazin(MagazinType model) {
        this.model = model;
    }
    private MagazinType model = null;

    public MagazinType getModel() {
        return model;
    }

    public void setModel(MagazinType model) {
        this.model = model;
    }

    public double getTotalFaraTaxe() {
        double rezultat = 0;
        for (Factura f : magazin) {
            rezultat += f.getTotalFaraTaxe();
        }
        return rezultat;
    }

    public double getTotalCuTaxe() {
        double rezultat = 0;
        for (Factura f : magazin) {
            rezultat += f.getTotalCuTaxe();
        }
        return rezultat;
    }

    public double getTotalCuTaxeScutite() {
        return getTotalCuTaxe() * calculScutiriTaxe();
    }

    public double getTotalTaraFaraTaxe(String tara) {
        double rezultat = 0;
        for (Factura f : magazin) {
            rezultat += f.getTotalTaraFaraTaxe(tara);
        }
        return rezultat;
    }

    public double getTotalTaraCuTaxe(String tara) {
        double rezultat = 0;
        for (Factura f : magazin) {
            rezultat += f.getTotalTaraCuTaxe(tara);
        }

        return rezultat;
    }

    public double getTotalTaraCuTaxeScutite(String tara) {
        return getTotalTaraCuTaxe(tara) * calculScutiriTaxe();
    }

    public String toString() {
        String s = "";
        System.out.println(nume);
        System.out.println();
        for (Factura f : magazin) {
            s += f.toString();
        }
        return s;

    }

    public abstract double calculScutiriTaxe();

}
