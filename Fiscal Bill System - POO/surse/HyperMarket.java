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
public class HyperMarket extends Magazin {

    public HyperMarket() {
        super(MagazinType.HYPER);
    }

    public double calculScutiriTaxe() {
        for (Factura f : magazin) {
            if (f.getTotalCuTaxe() > getTotalCuTaxe() / 10) {
                return 9.9;
            }

        }
        return 1;
    }
}
