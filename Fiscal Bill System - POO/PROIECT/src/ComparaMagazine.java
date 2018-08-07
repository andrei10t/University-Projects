
import java.util.Comparator;
import temapoo.Magazin;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Star Lord
 */
public class ComparaMagazine implements Comparator<Magazin> {
    public int compare(Magazin a, Magazin b){
        return (int) (50* (a.getTotalFaraTaxe()-b.getTotalFaraTaxe()));
    }
}
