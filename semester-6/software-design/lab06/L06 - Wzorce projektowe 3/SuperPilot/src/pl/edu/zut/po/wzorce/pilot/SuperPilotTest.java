package pl.edu.zut.po.wzorce.pilot;

import pl.edu.zut.po.wzorce.pilot.polecenia.*;
import pl.edu.zut.po.wzorce.pilot.sterowniki.*;


public class SuperPilotTest {
 
	public static void main(String[] args) {
		SuperPilot superPilot = new SuperPilot();
 
		Swiatlo salonSwiatlo = new Swiatlo("Salon");
		Swiatlo kuchniaSwiatlo = new Swiatlo("Kuchnia");
		WentylatorSufitowy wentylatorSufitowy = new WentylatorSufitowy("Salon");
		DrzwiGarazu DrzwiGarazowe = new DrzwiGarazu("Garaż");
		TV tv = new TV("Salon");
		WiezaStereo wiezaStereo = new WiezaStereo("Salon");
		Jacuzzi jacuzzi = new Jacuzzi();
		
		Polecenie salonSwiatloWlacz = new PolecenieWlaczSwiatlo(salonSwiatlo);
		Polecenie salonSwiatloWylacz = new PolecenieWylaczSwiatlo(salonSwiatlo);
		Polecenie kuchniaSwiatloWlacz = new PolecenieWlaczSwiatlo(kuchniaSwiatlo);
		Polecenie kuchniaSwiatloWylacz = new PolecenieWylaczSwiatlo(kuchniaSwiatlo);
		Polecenie wentylatorSyfitowyWlacz = new WentylatorSufitowyWysokieObroty(wentylatorSufitowy);
		Polecenie wentylatorSyfitowyWylacz = new WylaczWentylatorSufitowy(wentylatorSufitowy);
		Polecenie drzwiGarazoweOtworz = new OtworzDrzwiGarazowe(DrzwiGarazowe);
		Polecenie drzwiGarazoweZamknij = new ZamknijDrzwiGarazowe(DrzwiGarazowe);
		Polecenie wiezaStereoWlacz = new WiezaStereoWlaczCD(wiezaStereo);
		Polecenie wierzaStereoWylacz = new WylaczWiezaStereo(wiezaStereo);
		Polecenie wlaczSwiatlo20 = new PolecenieWlaczSwiatlo20(salonSwiatlo);
		Polecenie wlaczTV = new WlaczTv(tv);
		Polecenie wiezaStereoWlaczDVD = new WiezaStereoWlaczDVD(wiezaStereo);
		Polecenie przygotujJacuzzi = new PrzygotujJacuzzi(jacuzzi);
		Polecenie wylaczTV = new WylaczTv(tv);
		Polecenie wylaczWiezaStereo = new WylaczWiezaStereo(wiezaStereo);
		Polecenie wylaczJacuzzi = new WylaczJacuzzi(jacuzzi);


		MakroPolecenie wlaczWszystkieSwiatla = new WlaczWszystkieSwiatla(new Polecenie[] {salonSwiatloWlacz, kuchniaSwiatloWlacz});
		MakroPolecenie wylaczWszystkieSwiatla = new WylaczWszystkieSwiatla(new Polecenie[] {salonSwiatloWylacz, kuchniaSwiatloWylacz});
		MakroPolecenie trybImprezaWlacz = new WlaczTrybImpreza(new Polecenie[] {wlaczSwiatlo20,wlaczTV,wiezaStereoWlaczDVD,przygotujJacuzzi});
		MakroPolecenie trybImprezaWylacz = new WylaczTrybImpreza(new Polecenie[] {salonSwiatloWylacz,wylaczTV,wylaczWiezaStereo,wylaczJacuzzi});

		superPilot.ustawPolecenie(0, salonSwiatloWlacz, salonSwiatloWylacz);
		superPilot.ustawPolecenie(1, kuchniaSwiatloWlacz, kuchniaSwiatloWylacz);
		superPilot.ustawPolecenie(2, wentylatorSyfitowyWlacz, wentylatorSyfitowyWylacz);
		superPilot.ustawPolecenie(3, drzwiGarazoweOtworz, drzwiGarazoweZamknij);
		superPilot.ustawPolecenie(4, wiezaStereoWlacz, wierzaStereoWylacz);
		superPilot.ustawPolecenie(5, wlaczWszystkieSwiatla, wylaczWszystkieSwiatla);
		superPilot.ustawPolecenie(6, trybImprezaWlacz, trybImprezaWylacz);


		System.out.println(superPilot);
 
		superPilot.wcisnietoPrzyciskWlacz(0);
		superPilot.wcisnietoPrzyciskWycofaj();
		superPilot.wcisnietoPrzyciskWylacz(0);
		superPilot.wcisnietoPrzyciskWlacz(1);
		superPilot.wcisnietoPrzyciskWylacz(1);
		superPilot.wcisnietoPrzyciskWlacz(2);
		superPilot.wcisnietoPrzyciskWylacz(2);
		superPilot.wcisnietoPrzyciskWlacz(3);
		superPilot.wcisnietoPrzyciskWylacz(3);
		superPilot.wcisnietoPrzyciskWlacz(4);
		superPilot.wcisnietoPrzyciskWylacz(4);
		superPilot.wcisnietoPrzyciskWlacz(5);
		superPilot.wcisnietoPrzyciskWylacz(5);
		superPilot.wcisnietoPrzyciskWlacz(6);
		superPilot.wcisnietoPrzyciskWylacz(6);
	}
}
