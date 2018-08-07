/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

import static temapoo.MagazinType.HYPER;
import static temapoo.MagazinType.MEDIUM;
import static temapoo.MagazinType.MINI;

/**
 *
 * @author Star Lord
 */
public class MagazinFactory {
    public static Magazin buildMagazin(MagazinType model){
        Magazin magazin =null;
        switch(model){
            case MINI:
                magazin=new MiniMarket();
                break;
            
            case MEDIUM:
                magazin=new MediumMarket();
                break;
                
            case HYPER:
                magazin=new HyperMarket();
                break;
                
            default:
                break;
        }
        return magazin;
    }
}
