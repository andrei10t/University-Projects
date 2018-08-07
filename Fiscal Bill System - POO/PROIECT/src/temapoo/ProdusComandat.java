/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Vector;

/**
 *
 * @author Star Lord
 */
public class ProdusComandat {

    private Produs produs;
    private double taxa;
    private int cantitate;

    public ProdusComandat() {
    }

    public ProdusComandat(Produs produs, double taxa, int cantitate) {
        this.produs = produs;
        this.taxa = taxa;
        this.cantitate = cantitate;
    }

    public void setProdus(Produs produsNou) {
        produs = produsNou;
    }

    public Produs getProdus() {
        return produs;
    }

    public void setTaxa(double taxaNou) {
        taxa = taxaNou;
    }

    public double getTaxa() {
        return taxa;
    }

    public void setCantitate(int cantitateNou) {
        cantitate = cantitateNou;
    }

    public int getCantitate() {
        return cantitate;
    }

    public String toString() {
        String s = new String();
        return s + "nume: "+produs.getDenumire() + " categorie: " + produs.getCategorie() + " tara: "
                + produs.getTaraOrigine() + " taxa: " + taxa + " cantitate: " + cantitate+ " pret: "+ produs.getPret();

    }

    
}
