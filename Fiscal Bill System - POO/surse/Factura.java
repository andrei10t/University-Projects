/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

import java.util.List;
import java.util.Vector;

/**
 *
 * @author Star Lord
 */
public class Factura {

    String denumire;
    Vector<ProdusComandat> factura= new Vector<ProdusComandat>();
    
    public double getTotalCategorie(String categorie){
        double rezultat=0;
        for(ProdusComandat p:factura){
            if(p.getProdus().getCategorie().equals(categorie)){
                rezultat+=p.getCantitate()*p.getProdus().getPret()+
                        p.getCantitate()*p.getProdus().getPret()*p.getTaxa()/100;
            }
        }
        return rezultat;
    }
        
    public double getTotalFaraTaxe() {
        double rezultat = 0;
        for (ProdusComandat p : factura) {
            rezultat += p.getCantitate() * p.getProdus().getPret();
        }
        return rezultat;
    }

    public double getTotalCuTaxe() {
        double rezultat = 0;
        for (ProdusComandat p : factura) {
            rezultat += p.getCantitate() * p.getProdus().getPret() 
                    + p.getCantitate() * p.getTaxa() * p.getProdus().getPret() / 100;
        }
        return rezultat;
    }

    public double getTaxe() {
        double rezultat = 0;
        for (ProdusComandat p : factura) {
            rezultat += p.getCantitate() * p.getTaxa() * p.getProdus().getPret() / 100;
        }
        return rezultat;
    }

    public double getTotalTaraFaraTaxe(String tara) {
        double rezultat = 0;
        for (ProdusComandat p : factura) {
            if (p.getProdus().getTaraOrigine().equals(tara)) {
                rezultat += p.getCantitate() * p.getProdus().getPret();
            }
        }
        return rezultat;
    }

    public double getTotalTaraCuTaxe(String tara) {
        double rezultat = 0;
        for (ProdusComandat p : factura) {
            if (p.getProdus().getTaraOrigine().equals(tara)) {
                rezultat += p.getCantitate() * p.getProdus().getPret() 
                        + p.getCantitate() * p.getTaxa() * p.getProdus().getPret() / 100;
            }
        }
        return rezultat;
    }

    public double getTaxeTara(String tara) {
        double rezultat =0;
        for (ProdusComandat p : factura) {
            if (p.getProdus().getTaraOrigine().equals(tara)) {
                rezultat += p.getCantitate() * p.getTaxa() * p.getProdus().getPret() / 100;
            }
        }
        return rezultat;
       
    }
    public String toString(){
        String s="";
        for(ProdusComandat pc: factura){
            s+=pc.toString();
            s+="\n";
        }
        s+="\n";
        return s;
    }
    
}
