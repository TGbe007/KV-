#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"KVDBHandler.h"
#include<string>
using namespace std;
/*int main()
{
	string file;
	cout << "������Ҫ�򿪵����ݿ⣺";
	getline(cin, file);
	KVDBHandler handler((const string)file);
	int a[100] = { 3,1,1,1,3,2,2,3,2,1,1,2,1,2,2,3,1,1,1,1,1,3,2,2,3,3,3,2,1,3,2,2,1,1,2,2,1,1,3,2,2,1,1,3,3,1,1,2,2,2,3,3,2,1,1,2,2,1,2,3,1,2,3,3,3,3,3,3,3,2,3,3,1,1,3,3,2,3,2,3,2,1,1,3,1,2,3,1,2,3,1,1,2,1,1,1,3,1,3,3 };
	string str1[100] = { "B","N","H","J","X","N","T","S","Q","U","Z","F","R","C","C","V","M","D","D","U","B","Y","Q","W","H","W","S","J","G","Q","O","P","X","J","D","E","W","I","U","N","E","Y","O","I","K","W","F","E","K","H","J","Y","C","P","N","C","T","Y","M","W","I","H","P","E","I","T","J","G","B","X","X","R","O","Y","N","H","S","O","R","G","Q","F","Y","X","R","J","Y","V","W","V","V","O","O","S","F","Y","Z","H","Z","L" };
	string str2[100] = { "zzcpvanxtprlgi","upyablqgrktqc","hhdcunfttknenj","toyykgbacqfsbvk","wngdjbcqikztmxe","dcfshwtrfb","zoexnctvrvu","ykbthfazrx","dfbhadqika","vlgegadzmc","hoovsrgfxkat","ljyciehxcsoi","qfamenavmzikc","sbxynhqjwvndq","gicfrdnogbaukwe","qzykgkusqwvesq","nrifketlnqq","ugrjupnrktf","icdsksqdlny","orcwcwuakduee","twhevxmkvend","eqylggwhbt","ktzbvczjbcdtej","xgihqmfmudub","ygzupgtbankf","dvpxhrhdilzl","tdjkmdphpndmdhm","brencmdxsxsz","uxyhubddwj","jrywrdtlgjz","xlsyoxfypti","vbbmyckjnwiwwjb","gmfpyhqcjybu","vfedkcyptqt","qsxpqbukwt","xooejxaoigaqbr","detathnqfi","guzzzfwkapkp","zcnibbqfxvik","zzquamweiq","zbxwqilywog","sauklcqxklwdvdj","etnmhknlwrzaa","gzmcaqhhnpaxw","vazorqrnqu","ngsyqtbzfkly","sklsbpmnlmixh","ewbuoyniadod","hvprjlmvfmmiy","dckpmrnorshlke","nugcwljclmrgqbu","qgxdcwsdwzyit","mniygqawcc","ltxqqcaxcjltn","qutgckifvccwhvt","morzdxuqjk","kzvmgmndmhvtipq","aoeqhpjrtqjew","lbfptnvuyg","tvshimhzbkdv","ohxevakpbly","ebdoaxgrpwrex","jcenwicdty","jlmtddhsvzc","ocdqwiinttfpjr","kvthultzqruss","nnfcnvhqbgbxx","kpmmdeopkrtnzvd","wfctwpxigo","yplkpogxxemu","vyhxkekluk","kvaxnehirgighn","ktizimpaade","titznnruag","estfcqtqcvaok","rpwilrctaovjhzv","flxjwbtennig","uwpplxgast","hzrwqkidsdegvt","byhefyrdsy","tyadcfxutzgrw","jysryhqtta","rzhmhxpxlljp","jyvwxvpahcp","vktroxlrwmnwx","ihqtgmdrwkct","hpavchfskplopw","zkjxmbdppyf","runpgsjaomdnun","qbkqtndzzcvcwo","dgcseghznbdebwb","sjqitalqhbgvyqb","uousgbxypfb","bymoxkkzmue","cnttbcdhzrwszzd","sltczrlvrms","smjapfatyszjsoq","idwazihkjb","chdrwhuddvu","ehtqxrsjadyvn" };
	//a[i]=0��ʾ�滻���ݿ⣻a[i]=1��ʾset;2��ʾget;3��ʾdelete. str1����keyֵ��str2����valueֵ�� 
	for (int i = 0; i < 100; i++)
	{
		if (a[i] == 0)
		{
			getline(cin, file);
			handler.changefile(file);
		}
		if (a[i] == 1)
		{
			handler.Set(str1[i], str2[i]);
		}
		if (a[i] == 2)
		{
			string value;
			handler.Get(str1[i], value);
			if (value.size() == 0)
			{
				cout << "�Ҳ�����keyֵ��Ӧ��valueֵ." << endl;
			}
			else
			{
				cout << value << endl;
			}
		}
		if (a[i] == 3)
		{
			handler.Del(str1[i]);
		}
	}
	return 0;
}*/