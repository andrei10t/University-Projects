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
public class MiniMarket extends Magazin {

    MiniMarket() {
        super(MagazinType.MINI);
    }

    public double calculScutiriTaxe() {
        Citiri citire = new Citiri();
        for (String tara : citire.citireTari()) {
            if (getTotalTaraCuTaxe(tara) > (getTotalCuTaxe() / 2)) {
                return 0.9;
            }
        }
        return 1;
    }
}
