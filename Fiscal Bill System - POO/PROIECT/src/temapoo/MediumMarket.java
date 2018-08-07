/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

/**
 *
 * @author Star Lord
 */
public class MediumMarket extends Magazin {

    public MediumMarket() {
        super(MagazinType.MEDIUM);
    }

    public double calculScutiriTaxe() {
        Citiri citire = new Citiri();
        for (String c : citire.citireCategorie()) {
            if(getTotalCategorie(c) > getTotalCuTaxe()/2 )
                return 0.95;
        }
        return 1;
    }

}
