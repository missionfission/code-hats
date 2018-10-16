#include"hats_1.hpp"

sum_t loc_sum[tot_cell];
int_t cntmem[tot_cell][2];
int_t cnt[tot_cell];
aer memory[tot_cell][2][50];

sum_t svm(hist_t hist[rho][rho],int_t offset){
sum_t sum=0;
comp_t weights[tot_cell*rho*rho] = {-2.063528820872306824e-02,-1.158180594444274902e+00,4.317252337932586670e-01,-1.191073954105377197e-01,3.505196794867515564e-02,4.872589111328125000e-01,2.170588821172714233e-02,-1.333150863647460938e-01,-2.100706845521926880e-01,3.648332655429840088e-01,-7.803564667701721191e-01,-1.386398822069168091e-02,-2.051063925027847290e-01,1.972310431301593781e-02,1.112742796540260315e-01,2.495798915624618530e-01,-1.687575936317443848e+00,1.416517615318298340e+00,5.898873805999755859e-01,-3.370565474033355713e-01,-3.951647579669952393e-01,-3.469868898391723633e-01,3.324987292289733887e-01,1.416268348693847656e+00,2.485180944204330444e-01,8.250406980514526367e-01,-4.120576083660125732e-01,2.146018594503402710e-01,-7.007414847612380981e-02,3.856364488601684570e-01,4.699690937995910645e-01,1.987872123718261719e-01,-8.044598698616027832e-01,3.307057917118072510e-01,-8.562790155410766602e-01,6.153951957821846008e-02,3.740459084510803223e-01,-1.113300323486328125e+00,-4.934534728527069092e-01,-5.756611227989196777e-01,3.816262185573577881e-01,7.061353325843811035e-01,9.199784994125366211e-01,7.401596307754516602e-01,-7.085708975791931152e-01,-3.715169429779052734e-01,-3.807401657104492188e-01,1.919509917497634888e-01,7.534394264221191406e-01,3.657434880733489990e-01,-6.406591087579727173e-02,-8.117573857307434082e-01,-8.507340550422668457e-01,-1.251056641340255737e-01,1.150659918785095215e+00,7.379277944564819336e-01,3.647236227989196777e-01,-2.098214030265808105e-01,-1.193718075752258301e+00,2.970684468746185303e-01,-1.099312424659729004e+00,2.458080798387527466e-01,5.936311483383178711e-01,1.015103936195373535e+00,7.510262727737426758e-02,-1.543394923210144043e-01,1.073817729949951172e+00,5.399064719676971436e-02,7.411892414093017578e-01,-9.214034080505371094e-01,-1.984037995338439941e+00,-1.575863003730773926e+00,2.544961929321289062e+00,2.485612779855728149e-01,1.146762013435363770e+00,-4.266860783100128174e-01,-9.246576428413391113e-01,6.216380596160888672e-01,1.186421632766723633e+00,-1.769523620605468750e-01,2.954738028347492218e-02,-2.142123878002166748e-02,4.444923400878906250e-01,2.580829560756683350e-01,9.006572365760803223e-01,1.725320070981979370e-01,-6.879680752754211426e-01,-1.048326492309570312e+00,-1.246611237525939941e+00,-3.105770051479339600e-02,1.410173654556274414e+00,9.903985857963562012e-01,2.527248859405517578e-01,-3.681108951568603516e-01,-1.055569410324096680e+00,-5.336214303970336914e-01,-5.925685167312622070e-01,8.239042162895202637e-01,-6.598625779151916504e-01,-6.666193008422851562e-01,-5.969669222831726074e-01,4.269773066043853760e-01,3.335131704807281494e-01,7.239465117454528809e-01,-4.495376646518707275e-01,3.516954183578491211e-01,-5.658005475997924805e-01,-3.109689652919769287e-01,-3.328140377998352051e-01,4.878493845462799072e-01,-6.541938781738281250e-01,5.368232131004333496e-01,-2.506305277347564697e-01,1.776489317417144775e-01,5.500776693224906921e-02,1.039530634880065918e+00,-1.839091628789901733e-01,-3.203915357589721680e-01,2.429484724998474121e-01,-1.759082317352294922e+00,1.116054598242044449e-02,1.654319763183593750e+00,-6.091491505503654480e-02,9.231714010238647461e-01,2.445609867572784424e-01,-3.501110374927520752e-01,5.291398614645004272e-02,1.125972867012023926e+00,5.657300353050231934e-03,3.856687247753143311e-01,-8.947330117225646973e-01,-8.594620972871780396e-02,7.389871478080749512e-01,8.266060352325439453e-01,-2.091364115476608276e-01,-1.129337906837463379e+00,-5.529499053955078125e-01,-2.321061789989471436e-01,3.605402410030364990e-01,3.150246441364288330e-01,8.681440353393554688e-01,3.297046944499015808e-02,-9.378762245178222656e-01,-5.018738508224487305e-01,-3.334589302539825439e-01,-1.440800428390502930e-01,-6.099038720130920410e-01,1.577199548482894897e-01,-8.059906214475631714e-02,-7.463059425354003906e-01,6.442551016807556152e-01,1.450627148151397705e-01,-1.020537093281745911e-01,-2.064093202352523804e-01,2.688483297824859619e-01,-3.019934594631195068e-01,-5.573219060897827148e-02,4.294286370277404785e-01,-3.449833095073699951e-01,-3.075374960899353027e-01,1.120308879762887955e-02,1.122161224484443665e-01,1.735059320926666260e-01,1.135230422019958496e+00,-3.926463127136230469e-01,-3.773967921733856201e-01,-4.015000462532043457e-01,2.388725578784942627e-01,-1.611598968505859375e+00,-4.018473923206329346e-01,5.668334364891052246e-01,-4.434923082590103149e-02,6.582744121551513672e-01,-4.258929193019866943e-01,4.532437026500701904e-01,1.319433003664016724e-01,1.531144976615905762e-01,2.175765298306941986e-02,-2.815524339675903320e-01,8.372930288314819336e-01,6.112165451049804688e-01,4.437123537063598633e-01,1.051709175109863281e+00,-1.851923316717147827e-01,-1.334081411361694336e+00,-3.791015446186065674e-01,-4.947190582752227783e-01,1.537045389413833618e-01,1.584985256195068359e-01,-8.975607343018054962e-03,-2.488442212343215942e-01,6.445223093032836914e-01,-8.199482411146163940e-02,4.872210621833801270e-01,-8.021109104156494141e-01,4.837614595890045166e-01,-8.963739871978759766e-01,8.275405317544937134e-02,-5.364245176315307617e-01,-4.037986695766448975e-01,5.035460591316223145e-01,6.104064583778381348e-01,-4.820639491081237793e-01,-1.204866647720336914e+00,-2.146999686956405640e-01,8.107242584228515625e-01,3.684679865837097168e-01,-4.126115143299102783e-01,2.492147237062454224e-01,5.542204380035400391e-01,-4.134666323661804199e-01,1.085182070732116699e+00,2.734186649322509766e-01,-1.648267805576324463e-01,4.857286810874938965e-01,-3.567601144313812256e-01,-2.460103780031204224e-01,-4.658595025539398193e-01,-4.491264000535011292e-02,-7.819042801856994629e-01,-1.136793255805969238e+00,2.538673207163810730e-02,-4.379022121429443359e-01,6.499048471450805664e-01,5.529497265815734863e-01,7.383260726928710938e-01,3.105791509151458740e-01,1.734182536602020264e-01,-2.859898805618286133e-01,6.937208771705627441e-01,7.103215903043746948e-02,-1.905678659677505493e-01,1.202051863074302673e-01,7.427142560482025146e-02,-1.792018264532089233e-01,1.848017722368240356e-01,-3.265202045440673828e-01,-4.084483981132507324e-01,-7.080169916152954102e-01,4.091019630432128906e-01,1.316726803779602051e-01,-2.665021419525146484e-01,-2.912821173667907715e-01,-3.794196546077728271e-01,4.416735470294952393e-01,-3.521684110164642334e-01,-9.504520148038864136e-02,6.494833528995513916e-02,-5.117832869291305542e-02,-3.093076348304748535e-01,2.792536914348602295e-01,4.246114790439605713e-01,1.405332088470458984e-01,8.747549653053283691e-01,-1.574392169713973999e-01,2.169619686901569366e-02,1.279523968696594238e-01,-5.885731577873229980e-01,-6.748637557029724121e-01,5.958492159843444824e-01,6.867734789848327637e-01,9.779594540596008301e-01,-1.470729261636734009e-01,-1.033311724662780762e+00,2.951061725616455078e-01,-4.005764126777648926e-01,-5.479587316513061523e-01,-1.009029507637023926e+00,2.504734098911285400e-01,-2.630448043346405029e-01,5.460379719734191895e-01,2.508655190467834473e-01,3.047370016574859619e-01,-1.062335669994354248e-01,-1.303351372480392456e-01,-6.923545151948928833e-02,-8.347692489624023438e-01,-9.316904097795486450e-02,7.744941115379333496e-01,3.870335873216390610e-03,-5.639175176620483398e-01,-9.854926466941833496e-01,9.517877697944641113e-01,4.014381468296051025e-01,-1.968361884355545044e-01,2.100589275360107422e-01,-4.356326758861541748e-01,1.312045007944107056e-01,-3.860868513584136963e-01,2.868453562259674072e-01,6.039516329765319824e-01,-3.769495785236358643e-01,-7.260179519653320312e-02,1.927358955144882202e-01,2.025384455919265747e-01,-2.440479546785354614e-01,-5.409696698188781738e-01,4.570827186107635498e-01,2.869071960449218750e-01,1.880923658609390259e-01,4.037222266197204590e-02,-7.283350825309753418e-01,2.718355655670166016e-01,2.904218137264251709e-01,9.700288176536560059e-01,-3.137916028499603271e-01,4.162858426570892334e-01,2.512373030185699463e-01,-1.117174863815307617e+00,6.738966107368469238e-01,6.946153640747070312e-01,-4.050558507442474365e-01,3.910634815692901611e-01,7.166828960180282593e-02,-2.979726791381835938e-01,-1.220423057675361633e-01,-2.179566770792007446e-01,-5.862891674041748047e-01,-1.335329413414001465e+00,-6.906896233558654785e-01,-2.261866480112075806e-01,2.414732426404953003e-01,2.753794193267822266e-01,6.381279826164245605e-01,-6.647280603647232056e-02,7.193073630332946777e-01,-3.353726863861083984e-02,-8.653991222381591797e-01,-8.828637003898620605e-02,-3.586712181568145752e-01,2.996748983860015869e-01,3.864821046590805054e-03,8.110529184341430664e-02,4.387803375720977783e-01,7.883923649787902832e-01,1.703577041625976562e-01,2.408319413661956787e-01,5.139469727873802185e-02,9.843542426824569702e-02,-4.082830548286437988e-01,4.531365633010864258e-01,1.560819745063781738e-01,2.337556034326553345e-01,-3.997330069541931152e-01,-1.068425551056861877e-01,-1.067772358655929565e-01,7.350695729255676270e-01,-6.356967240571975708e-02,-2.556990981101989746e-01,5.492063164710998535e-01,-4.622718393802642822e-01,-1.069458872079849243e-01,1.138801455497741699e+00,-2.159212082624435425e-01,-6.480175256729125977e-02,-6.127419471740722656e-01,-3.715995848178863525e-01,1.599598228931427002e-01,7.835696339607238770e-01,6.305183768272399902e-01,1.347172558307647705e-01,7.709003239870071411e-02,-3.631863892078399658e-01,-4.670447111129760742e-01,-5.253173708915710449e-01,3.997528553009033203e-01,3.629539310932159424e-01,-6.365916728973388672e-01,-2.132558226585388184e-01,6.669826507568359375e-01,-1.455978751182556152e-01,-1.217287182807922363e-01,3.606753945350646973e-01,2.459677755832672119e-01,1.064073324203491211e+00,-8.847777545452117920e-02,-3.028034269809722900e-01,-4.341030120849609375e-01,-4.523971080780029297e-01,8.114160597324371338e-02,-1.647480949759483337e-02,-6.616111844778060913e-02,2.804113030433654785e-01,-3.365796208381652832e-01,-5.687201619148254395e-01,-5.977369546890258789e-01,-7.399350404739379883e-01,-6.307635307312011719e-01,-1.184581041336059570e+00,-1.158870905637741089e-01,2.350314408540725708e-01,-7.490978459827601910e-04,6.382136046886444092e-02,1.781016290187835693e-01,-2.621054351329803467e-01,-1.792850941419601440e-01,3.487507626414299011e-02,-1.079895570874214172e-01,-8.699393272399902344e-01,2.078256458044052124e-01,-3.045747280120849609e-01,-1.695098578929901123e-01,5.500595569610595703e-01,-3.419607579708099365e-01,-2.982025444507598877e-01,-5.652800318785011768e-04,3.659277558326721191e-01,-1.660355925559997559e-01,3.512274026870727539e-01,8.915941119194030762e-01,-1.522157341241836548e-01,-5.541612505912780762e-01,-5.978326797485351562e-01,2.877362370491027832e-01,4.215530753135681152e-01,3.838977515697479248e-01,-8.536468148231506348e-01,-4.305607974529266357e-01,1.079625561833381653e-01,-1.541281938552856445e-01,-2.238544970750808716e-01,4.870883524417877197e-01,-1.078248098492622375e-01,6.229589581489562988e-01,-3.166539669036865234e-01,-4.593064486980438232e-01,-1.830288171768188477e-01,1.454420834779739380e-01,7.310349494218826294e-02,-2.281799167394638062e-01,1.243171095848083496e-01,2.589771747589111328e-01,-3.420116901397705078e-01,5.772965028882026672e-02,-1.777637451887130737e-01,-2.527252435684204102e-01,-4.632200598716735840e-01,-4.530105888843536377e-01,-2.852672897279262543e-02,-1.575378477573394775e-01,-3.844423592090606689e-01,-6.587922573089599609e-02,7.037685066461563110e-02,-2.501292228698730469e-01,-5.831388290971517563e-03,1.889111995697021484e-01,2.624248862266540527e-01,5.366543307900428772e-02,-1.349804252386093140e-01,-5.861104652285575867e-02,2.679315023124217987e-02,-1.160741448402404785e-01,1.560884993523359299e-02,2.357261031866073608e-01,8.234372735023498535e-02,-8.390547335147857666e-02,-4.537628218531608582e-02,-1.216736212372779846e-01,-2.245013415813446045e-02,1.879471391439437866e-01,-1.040481179952621460e-01,8.963826298713684082e-02,-1.101782396435737610e-01,-2.058394104242324829e-01,-3.283406794071197510e-01,-5.247309207916259766e-01,-1.354020182043313980e-02,7.927192002534866333e-02,1.329653263092041016e-01,-2.042677253484725952e-01,-4.243988394737243652e-01,-3.649586141109466553e-01,6.025963649153709412e-02,3.614574670791625977e-03,4.217154160141944885e-02,4.810009524226188660e-02,-2.760567367076873779e-01,-4.134251773357391357e-01,-5.274238586425781250e-01,2.272964566946029663e-01,-6.458712369203567505e-02,-1.003268957138061523e-01,-5.254586786031723022e-02,-4.137714579701423645e-02,-5.339319631457328796e-02,-1.866416037082672119e-01,-4.108121618628501892e-02,1.767369508743286133e-01,4.892856813967227936e-03,-4.374875128269195557e-02,-9.983022212982177734e-01,4.310277104377746582e-01,-3.813969194889068604e-01,5.876638889312744141e-01,6.559305787086486816e-01,-6.692793965339660645e-01,1.709010154008865356e-01,1.174113303422927856e-01,1.880206167697906494e-01,-3.178015351295471191e-01,1.110011935234069824e-01,-1.357364505529403687e-01,-6.487751007080078125e-01,4.675822257995605469e-01,3.048921823501586914e-01,-3.011192195117473602e-02,-2.813478410243988037e-01,8.257351517677307129e-01,-3.001836240291595459e-01,5.097170546650886536e-02,-2.685858309268951416e-01,-1.156715154647827148e+00,-1.201030135154724121e+00,6.020566225051879883e-01,-6.714336872100830078e-01,2.420489639043807983e-01,-1.059256270527839661e-01,-1.134123563766479492e+00,-5.654828548431396484e-01,5.739796534180641174e-02,1.057724714279174805e+00,9.102353453636169434e-01,-1.269867867231369019e-01,8.067636489868164062e-01,1.091501861810684204e-01,4.468171894550323486e-01,4.162490963935852051e-01,4.713152050971984863e-01,-1.092320442199707031e+00,-5.151018500328063965e-01,4.974808394908905029e-01,-7.455451786518096924e-02,-5.963138863444328308e-02,2.831312417984008789e-01,-1.360806941986083984e+00,5.556730031967163086e-01,-6.935377120971679688e-01,3.400778174400329590e-01,8.118935227394104004e-01,9.418834447860717773e-01,-3.655798733234405518e-01,-9.670321941375732422e-01,5.299515128135681152e-01,-2.653645277023315430e-01,-4.047530591487884521e-01,3.917054831981658936e-01,9.085555076599121094e-01,-5.760193467140197754e-01,-1.687080979347229004e+00,2.806342244148254395e-01,-6.486633419990539551e-01,4.878076612949371338e-01,7.872126698493957520e-01,9.346277117729187012e-01,-3.781791329383850098e-01,-2.259270548820495605e-01,1.562365651130676270e+00,4.522390961647033691e-01,3.341979980468750000e-01,3.745462298393249512e-01,-1.520093679428100586e+00,-6.764798760414123535e-01,1.094019532203674316e+00,1.598976254463195801e-01,1.357874989509582520e+00,-1.447888970375061035e+00,-9.339039921760559082e-01,-6.068165898323059082e-01,5.257025361061096191e-01,1.337755203247070312e+00,4.409371614456176758e-01,3.687011599540710449e-01,-8.577911853790283203e-01,-9.259257316589355469e-01,5.356487631797790527e-01,5.655050873756408691e-01,-1.351681470870971680e+00,-6.278572678565979004e-01,-3.624406456947326660e-01,3.778413534164428711e-01,1.699368953704833984e+00,-1.877322234213352203e-02,-6.010985374450683594e-02,-4.152439534664154053e-01,-7.275247573852539062e-01,4.893503785133361816e-01,-5.358562469482421875e-01,6.812639236450195312e-01,-1.405174005776643753e-02,-8.112829923629760742e-01,6.535655260086059570e-02,7.628463506698608398e-01,5.170024037361145020e-01,-9.342020004987716675e-02,3.418925404548645020e-01,3.911609351634979248e-01,6.901301145553588867e-01,-9.743768572807312012e-01,5.040877461433410645e-01,-5.036015510559082031e-01,-1.033104896545410156e+00,3.857724666595458984e-01,7.115527987480163574e-01,-7.365443706512451172e-01,-2.100773006677627563e-01,1.133374869823455811e-01,-3.516406416893005371e-01,-2.834998071193695068e-01,2.618338763713836670e-01,-1.903001904487609863e+00,-1.100580930709838867e+00,1.195985078811645508e+00,5.493414029479026794e-02,1.378572940826416016e+00,-6.341913342475891113e-01,-2.147715389728546143e-01,1.685885637998580933e-01,9.736897945404052734e-01,3.426727354526519775e-01,2.703432142734527588e-01,-9.037373661994934082e-01,-8.248910307884216309e-01,5.914606451988220215e-01,7.011271119117736816e-01,6.665744781494140625e-01,-2.759230434894561768e-01,9.714157879352569580e-02,-4.626245796680450439e-01,-3.389726579189300537e-01,-2.053436934947967529e-01,2.751113474369049072e-01,-9.467773437500000000e-01,-5.849374532699584961e-01,2.337994873523712158e-01,1.376566171646118164e+00,3.122869431972503662e-01,4.125241041183471680e-01,-4.336502850055694580e-01,-1.124087929725646973e+00,-4.277437031269073486e-01,3.282884061336517334e-01,4.764579534530639648e-01,-3.364178240299224854e-01,2.204181104898452759e-01,1.211519911885261536e-02,4.564504027366638184e-01,1.962717995047569275e-02,2.859558463096618652e-01,1.608452200889587402e-01,6.626592576503753662e-02,8.589601516723632812e-01,2.138017416000366211e-01,1.544311046600341797e-01,3.359012305736541748e-01,-4.857356548309326172e-01,-2.481772191822528839e-02,2.158652395009994507e-01,-3.659307360649108887e-01,-3.380570709705352783e-01,-1.045585125684738159e-01,8.628478050231933594e-01,-3.441590070724487305e-01,-1.679434627294540405e-01,-1.278474181890487671e-01,-1.020006895065307617e+00,-3.709565997123718262e-01,1.326797902584075928e-01,4.457536935806274414e-01,7.577817440032958984e-01,-3.723106384277343750e-01,-1.401660740375518799e-01,7.370015233755111694e-02,-5.536191537976264954e-02,-1.387176513671875000e-01,-1.395698357373476028e-02,3.813022673130035400e-01,1.700231134891510010e-01,1.433699131011962891e-01,-5.688523501157760620e-02,-4.139157831668853760e-01,-2.068028599023818970e-01,-4.823991060256958008e-01,-2.521845698356628418e-01,1.800966560840606689e-01,-1.047632694244384766e+00,2.221358865499496460e-01,-3.235466480255126953e-01,4.055550321936607361e-02,5.796346068382263184e-01,-1.107547730207443237e-01,-1.630942374467849731e-01,-8.700349330902099609e-01,2.458021342754364014e-01,-1.052185416221618652e+00,-2.247609794139862061e-01,1.582004427909851074e-01,-2.708870731294155121e-02,3.576276004314422607e-01,4.669674038887023926e-01,-7.648534774780273438e-01,3.535675406455993652e-01,1.014055386185646057e-01,-2.704614698886871338e-01,-2.818651124835014343e-02,-2.119502276182174683e-01,2.726592496037483215e-02,2.851228415966033936e-01,2.219253033399581909e-01,3.758323490619659424e-01,2.985666394233703613e-01,5.689889658242464066e-03,-6.149130463600158691e-01,-3.186092078685760498e-01,9.735387563705444336e-02,4.775189161300659180e-01,-8.231311440467834473e-01,2.852018475532531738e-01,-4.173051118850708008e-01,3.453033864498138428e-01,8.677124381065368652e-01,4.271303117275238037e-01,1.240433081984519958e-01,-8.810558915138244629e-02,-1.692614406347274780e-01,-1.729672253131866455e-01,-2.164714485406875610e-01,2.068393081426620483e-01,-3.478446230292320251e-02,-6.020512580871582031e-01,-5.238459706306457520e-01,5.616746842861175537e-02,5.074020624160766602e-01,2.149774134159088135e-01,-5.980044007301330566e-01,3.098790645599365234e-01};
//#pragma HLS RESOURCE variable=weights core=ROM_nP_BRAM latency=1
#pragma HLS pipeline
for(int_t i=0;i<rho;i++){
#pragma HLS unroll factor = N_PE/2
	for(int_t j=0;j<rho;j++){
#pragma HLS unroll factor = N_PE
		sum+=(hist[i][j]*weights[offset+i*rho+j]);
//		cout<<weights[offset+i*rho+j]<<"  "<<hist[i][j]<<"   "<< hist[i][j]*weights[offset+i*rho+j]<<"  "<<sum<<"\n";
		}
}
return sum;
}
void computeHistogram(addr_t cell_id,aer event)
{

hist_t hist[rho][rho]={0};
for (int i=0;i<rho;i++)
	for (int j=0;j<rho;j++)
		hist[i][j]=0;
//#pragma HLS array_partition variable=hist dim=0
//#pragma HLS RESOURCE variable=hist core=RAM_2P_BRAM latency=2
for(int i=0;i<rho;i++)
	for(int j=0;j<rho;j++)
			hist[i][j]=0;
for(int_t i=0;i<cntmem[cell_id][event.p];i++)
	{
#pragma HLS loop_tripcount min=5 max=80 avg=30
	 int_t x=memory[cell_id][event.p][i].y-event.y;
	 int_t y=memory[cell_id][event.p][i].x-event.x;
        if(abs(x)<=rho/2 && abs(y)<=rho/2)
      {
        	hist[x+rho/2][y+rho/2]++;
//    		hist[x+rho/2][y+rho/2]+=(1-(event.t-memory[cell_id][event.p][i].t)/tau);
//      int k=1-(event.t-memory[cell_id][event.p][i].t)/tau;
//      cout<<hist[x+rho/2][y+rho/2]<<"  "<<k<<endl;
      }
	}
	int_t offset= cell_id*rho*rho;
 loc_sum[cell_id]+=svm(hist,offset);
}
sum_t hats(aer events[],int_t size)
{

#pragma HLS DATA_PACK variable=events struct_level
#pragma HLS INTERFACE ap_fifo port=events depth=1500 bundle=events
#pragma HLS INTERFACE s_axilite port=size
#pragma HLS INTERFACE s_axilite port=return
sum_t sum=0;
addr_t cell_id;
#pragma HLS RESOURCE variable=cnt core=RAM_2P_BRAM latency=1
#pragma HLS RESOURCE variable=memory core=RAM_2P_BRAM latency=1
#pragma HLS RESOURCE variable=cntmem core=RAM_2P_BRAM latency=1
#pragma HLS reset variable=cnt
#pragma HLS reset variable=cntmem
#pragma HLS reset variable=loc_sum
//memset(cnt, 0, sizeof(cnt[0])*tot_cell);
//memset(cntmem, 0, sizeof(cntmem[0][0])*tot_cell*2);

//for (int_t i=0;i<tot_cell;i++)
//	{
//	#pragma HLS unroll
//	loc_sum[i]=0;
//	cnt[i]=0 ;
//	cntmem[i][0]=0;
//	cntmem[i][1]=0;}
for(int_t j=0;j<size;j++)
	{
	#pragma HLS loop_tripcount min=0 max=900
//	cell_id= (events[j].y)/10;
	cell_id= ((events[j].x)/10)*10+(events[j].y)/10;
	computeHistogram(cell_id,events[j]);
	memory[cell_id][events[j].p][cntmem[cell_id][events[j].p]]=events[j];
	cntmem[cell_id][events[j].p]++;
	cnt[cell_id]++;
	}
//#pragma HLS pipeline
for(int_t k=0;k<tot_cell;k++)
{
	#pragma HLS unroll factor=3
	if(cnt[k]>0)
sum+=loc_sum[k]/cnt[k];
//cout<<sum<<"  "<<loc_sum[k]<<endl;
}
//cout<<sum<<endl;
return sum;
}

