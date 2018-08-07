/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

import java.util.Comparator;

/**
 *
 * @author Star Lord
 */

    public class ComparaMagazinele implements Comparator<Magazin> {
    public int compare(Magazin a, Magazin b){
        return (int) (50* (a.getTotalFaraTaxe()-b.getTotalFaraTaxe()));
    }
}

