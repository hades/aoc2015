// Copyright John Maddock 2006.
// Copyright Paul A. Bristow 2007, 2009
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_MATH_OVERFLOW_ERROR_POLICY ignore_error

#include <boost/math/concepts/real_concept.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>
#include <boost/math/tools/stats.hpp>
#include <boost/math/tools/test.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/array.hpp>
#include "functor.hpp"

#include "handle_test_result.hpp"
#include "table_type.hpp"

#include <boost/math/special_functions/hypergeometric_0F1.hpp>

template <class Real, class T>
void do_test_0F1(const T& data, const char* type_name, const char* test_name)
{
   typedef Real                   value_type;

   typedef value_type(*pg)(value_type, value_type);
#if defined(BOOST_MATH_NO_DEDUCED_FUNCTION_POINTERS)
   pg funcp = boost::math::hypergeometric_0F1<value_type, value_type>;
#else
   pg funcp = boost::math::hypergeometric_0F1;
#endif

   boost::math::tools::test_result<value_type> result;

   std::cout << "Testing " << test_name << " with type " << type_name
      << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

   //
   // test hypergeometric_0F1 against data:
   //
   result = boost::math::tools::test_hetero<Real>(
      data,
      bind_func<Real>(funcp, 0, 1),
      extract_result<Real>(2));
   handle_test_result(result, data[result.worst()], result.worst(), type_name, "hypergeometric_0F1", test_name);
   std::cout << std::endl;
}

template <class T>
void test_spots(T, const char* type_name)
{
#ifndef SC_
#define SC_(x) BOOST_MATH_BIG_CONSTANT(T, 1000000, x)
#endif

   //
   // basic sanity checks, tolerance is 10 epsilon expressed as a percentage:
   //
   BOOST_CHECK_EQUAL(boost::math::hypergeometric_0F1(T(3), T(0)), 1);
   BOOST_CHECK_EQUAL(boost::math::hypergeometric_0F1(T(-3), T(0)), 1);
   BOOST_CHECK_EQUAL(boost::math::hypergeometric_0F1(T(0), T(0)), 1);

   BOOST_CHECK_THROW(boost::math::hypergeometric_0F1(T(0), T(-1)), std::domain_error);
   BOOST_CHECK_THROW(boost::math::hypergeometric_0F1(T(-1), T(-1)), std::domain_error);
   BOOST_CHECK_THROW(boost::math::hypergeometric_0F1(T(-10), T(-5)), std::domain_error);

   static const std::array<std::array<T, 3>, 50> hypergeometric_0F1_integer_data = { {
      { SC_(4.0), SC_(-20.0),  SC_(-0.012889714201783047561923257996127233830940165138385) },
      { SC_(8.0), SC_(-20.0),  SC_(0.046498609282365144223175012935939437508273248399881) },
      { SC_(12.0), SC_(-20.0),  SC_(0.16608847431869756642136191351311569335145459224622) },
      { SC_(16.0), SC_(-20.0),  SC_(0.27230484709157170329168048388841880599105216477631) },
      { SC_(20.0), SC_(-20.0),  SC_(0.35865872656868844615709101792040025253126126604266) },
      { SC_(4.0), SC_(-16.0),  SC_(-0.027293644412433023379286103818840667403690937153604) },
      { SC_(8.0), SC_(-16.0),  SC_(0.098618710511372349330666801041676087431136532039702) },
      { SC_(12.0), SC_(-16.0),  SC_(0.24360114226383905073379763460037817885919457531523) },
      { SC_(16.0), SC_(-16.0),  SC_(0.35635186318802906043824855864337727878754460163525) },
      { SC_(20.0), SC_(-16.0),  SC_(0.44218381382689101428948260613085371477815110358789) },
      { SC_(4.0), SC_(-12.0),  SC_(-0.021743572290699436419371120781513860006290363262907) },
      { SC_(8.0), SC_(-12.0),  SC_(0.19025625754362006866949730683824627505504067855043) },
      { SC_(12.0), SC_(-12.0),  SC_(0.35251228238278927379621049815222218665165551016489) },
      { SC_(16.0), SC_(-12.0),  SC_(0.46415411486674623230458980010115972932474705884865) },
      { SC_(20.0), SC_(-12.0),  SC_(0.54394918325286018927327004362535051310016558628741) },
      { SC_(4.0), SC_(-8.0),  SC_(0.056818744289274872033266550620647787396712125304880) },
      { SC_(8.0), SC_(-8.0),  SC_(0.34487371876996263249797701802458885718691612997456) },
      { SC_(12.0), SC_(-8.0),  SC_(0.50411654015891701804499796523449656998841355305043) },
      { SC_(16.0), SC_(-8.0),  SC_(0.60191459981670594041254437708158847428118361245442) },
      { SC_(20.0), SC_(-8.0),  SC_(0.66770752550930138035694866478078941681114294465418) },
      { SC_(4.0), SC_(-4.0),  SC_(0.32262860540671645526863760914000166725449779629143) },
      { SC_(8.0), SC_(-4.0),  SC_(0.59755773349355150397404772151441126513126998265958) },
      { SC_(12.0), SC_(-4.0),  SC_(0.71337465206009117934071859694314971137807212605147) },
      { SC_(16.0), SC_(-4.0),  SC_(0.77734333649378860739496954157535257278092349684783) },
      { SC_(20.0), SC_(-4.0),  SC_(0.81794177985447769150469288350369205683856312760890) },

      { SC_(4.0), SC_(4.0),  SC_(2.5029568338152582758923890008139391395035041790831) },
      { SC_(8.0), SC_(4.0),  SC_(1.6273673128576761227855719910743734060605725722129) },
      { SC_(12.0), SC_(4.0),  SC_(1.3898419290864057799739567227851793491657442624207) },
      { SC_(16.0), SC_(4.0),  SC_(1.2817098157957427946677711269410726972209834860612) },
      { SC_(20.0), SC_(4.0),  SC_(1.2202539302152377230940386181201477276788392792437) },
      { SC_(4.0), SC_(8.0),  SC_(5.5616961007411965409200003309686924059253894118586) },
      { SC_(8.0), SC_(8.0),  SC_(2.5877053985451664722152913482683136948296873738479) },
      { SC_(12.0), SC_(8.0),  SC_(1.9166410733572697158003086323981583993970490592046) },
      { SC_(16.0), SC_(8.0),  SC_(1.6370675016890669952237854163997946987362497613701) },
      { SC_(20.0), SC_(8.0),  SC_(1.4862852701827990444915220582410007454379891584086) },
      { SC_(4.0), SC_(12.0),  SC_(11.419268276211177842169936131590385979116019595164) },
      { SC_(8.0), SC_(12.0),  SC_(4.0347215359576567066789638314925802225312840819037) },
      { SC_(12.0), SC_(12.0),  SC_(2.6242497527837800417573064942486918368886996538285) },
      { SC_(16.0), SC_(12.0),  SC_(2.0840468784170876805932772732753387258909164486511) },
      { SC_(20.0), SC_(12.0),  SC_(1.8071042457762091748544382847762106786633952487005) },
      { SC_(4.0), SC_(16.0),  SC_(22.132051970576036053853444648907108439504682530918) },
      { SC_(8.0), SC_(16.0),  SC_(6.1850485247748975008808779795786699492711191898792) },
      { SC_(12.0), SC_(16.0),  SC_(3.5694322843488018916484224923627864928705138154372) },
      { SC_(16.0), SC_(16.0),  SC_(2.6447371137201451261118187672029372265909501355722) },
      { SC_(20.0), SC_(16.0),  SC_(2.1934058398888071720297525592515838555602675797235) },
      { SC_(4.0), SC_(20.0),  SC_(41.021743268279206331672552645354782698296383424328) },
      { SC_(8.0), SC_(20.0),  SC_(9.3414225299809886395081381945971250426599939097753) },
      { SC_(12.0), SC_(20.0),  SC_(4.8253866205826406499959001774187695527272168375992) },
      { SC_(16.0), SC_(20.0),  SC_(3.3462305133519485784864062004430532216764447939942) },
      { SC_(20.0), SC_(20.0),  SC_(2.6578698872220394617444624241257799193518140676691) },
      } };

   static const std::array<std::array<T, 3>, 121> hypergeometric_0F1_real_data = { {
      { SC_(-20.25), SC_(-20.25), SC_(2.7957722939837585922721916572828265337379885810463) },
      {SC_(-20.25), SC_(-16.25), SC_(2.2711152061687223613453898226719770018304527545367) },
      {SC_(-20.25), SC_(-12.25), SC_(1.8494593608212709260834907188011226625504792564008) },
      {SC_(-20.25), SC_(-8.25), SC_(1.5096123122209879279439571483106546579344083224475) },
      {SC_(-20.25), SC_(-4.25), SC_(1.2349600261245108147217156468676391406107607937783) },
      {SC_(-20.25), SC_(-0.25), SC_(1.0124262131477737489760461958823145562583738548481) },
      {SC_(-20.25), SC_(3.75), SC_(0.83168105368847042690250207452503923498261925399290) },
      {SC_(-20.25), SC_(7.75), SC_(0.68453616446705348287989858944821561345027038288523) },
      {SC_(-20.25), SC_(11.75), SC_(0.56447959084730590158981806575147730464939958811641) },
      {SC_(-20.25), SC_(15.75), SC_(0.46631672324832840040099031042536652056451149930724) },
      {SC_(-20.25), SC_(19.75), SC_(0.38589178960453729031753371638509489720353970202557) },
      {SC_(-16.25), SC_(-20.25), SC_(3.6853033678389815793858749638872118256381350051933) },
      {SC_(-16.25), SC_(-16.25), SC_(2.8189932976213221794412912826715210157252407675492) },
      {SC_(-16.25), SC_(-12.25), SC_(2.1683206814848382415951069178541485022190389032861) },
      {SC_(-16.25), SC_(-8.25), SC_(1.6762781419304165453124288212144469387497248544980) },
      {SC_(-16.25), SC_(-4.25), SC_(1.3019174596541545423250019596925072929338360502457) },
      {SC_(-16.25), SC_(-0.25), SC_(1.0155114597289924802082858072926838795825629097345) },
      {SC_(-16.25), SC_(3.75), SC_(0.79528104007050457443200675888120572482230255556703) },
      {SC_(-16.25), SC_(7.75), SC_(0.62514113457518737301424222399549180276283312092061) },
      {SC_(-16.25), SC_(11.75), SC_(0.49312611939645449055396232495817215814052621005108) },
      {SC_(-16.25), SC_(15.75), SC_(0.39027640231656357551572959324213784623094177949066) },
      {SC_(-16.25), SC_(19.75), SC_(0.30983458381312295039033218076191326310645958859520) },
      {SC_(-12.25), SC_(-20.25), SC_(6.1704666666278938283835490432795642056267750516111) },
      {SC_(-12.25), SC_(-16.25), SC_(4.1552272888330207621302106989548328150305062793812) },
      {SC_(-12.25), SC_(-12.25), SC_(2.8629405204600569631773103187639297768454467434670) },
      {SC_(-12.25), SC_(-8.25), SC_(2.0050800521989931571210090020740770238121125995302) },
      {SC_(-12.25), SC_(-4.25), SC_(1.4226882175494078094616273681832235056660520864074) },
      {SC_(-12.25), SC_(-0.25), SC_(1.0206367767231596623643982724086720984175407326239) },
      {SC_(-12.25), SC_(3.75), SC_(0.73925379130945509368577275378254380866098045869975) },
      {SC_(-12.25), SC_(7.75), SC_(0.54000881441780813642748748511053584681016992673867) },
      {SC_(-12.25), SC_(11.75), SC_(0.39734252271724847449760568202775839997979417321096) },
      {SC_(-12.25), SC_(15.75), SC_(0.28584659061590258036270241201657559564217479119707) },
      {SC_(-12.25), SC_(19.75), SC_(-0.0081173945118881955152340569022581720505805271716412) },
      {SC_(-8.25), SC_(-20.25), SC_(30.214776746264667028399437825207186990952563144565) },
      {SC_(-8.25), SC_(-16.25), SC_(13.206923736113233408873312298765667487728366521206) },
      {SC_(-8.25), SC_(-12.25), SC_(5.8765290507182112008139505719133766922110698377617) },
      {SC_(-8.25), SC_(-8.25), SC_(2.9943833929883303847073818502561706078874721587174) },
      {SC_(-8.25), SC_(-4.25), SC_(1.7091345745360580812285240901667243909385176010261) },
      {SC_(-8.25), SC_(-0.25), SC_(1.0308325464760906146441689208198464885112314788329) },
      {SC_(-8.25), SC_(3.75), SC_(0.64304308306518963175886701666419407366549702609687) },
      {SC_(-8.25), SC_(7.75), SC_(0.37629752350234203158515342524983705294147434733076) },
      {SC_(-8.25), SC_(11.75), SC_(-2.1055871696987101269944140698868945037062228729050) },
      {SC_(-8.25), SC_(15.75), SC_(-50.562697627448074052585932806347970082382096647974) },
      {SC_(-8.25), SC_(19.75), SC_(-579.94915881084897988862450916571551198001894291852) },
      { SC_(-4.25), SC_(-20.25), SC_(-66.582207191755226871227185886830083823068161088090) }, {SC_(-4.25), SC_(-16.25), SC_(0.99585574579280575697804972744074637223473969232632)}, {SC_(-4.25), SC_(-12.25), SC_(23.510774658631484713205463401664873191546111331469)}, {SC_(-4.25), SC_(-8.25), SC_(14.506347207276003438062329264569459812455033677057)}, {SC_(-4.25), SC_(-4.25), SC_(3.8047736693317086794526961473100619698786965398531)}, {SC_(-4.25), SC_(-0.25), SC_(1.0611747490912035255122776417926285437513018011867)}, {SC_(-4.25), SC_(3.75), SC_(-0.80390254520675152395475412235031817082929562419835)}, {SC_(-4.25), SC_(7.75), SC_(-100.43339815718209139439327680390551018715836820761)}, {SC_(-4.25), SC_(11.75), SC_(-1533.8025906900325906352282963205257001995564543560)}, {SC_(-4.25), SC_(15.75), SC_(-11903.890928701912286627232258091180714843387637568)}, {SC_(-4.25), SC_(19.75), SC_(-63573.720858843295034857393096900086420282088096223)},
      {SC_(-0.25), SC_(-20.25), SC_(5.8154983455887482996117997327072965277711303658190)}, {SC_(-0.25), SC_(-16.25), SC_(7.8645427110771775078914759561882836266181443022557)}, {SC_(-0.25), SC_(-12.25), SC_(2.8859855860040835605817890532890777322459344278127)}, {SC_(-0.25), SC_(-8.25), SC_(-4.4978057721216329075474975538674330456610136767402)}, {SC_(-0.25), SC_(-4.25), SC_(-3.2843951886889091457664917868727091433634846305430)}, {SC_(-0.25), SC_(-0.25), SC_(1.8410918501257885334774939532672407660260932497146)}, {SC_(-0.25), SC_(3.75), SC_(-89.507839434346979238664123270851349643390027303630)}, {SC_(-0.25), SC_(7.75), SC_(-684.94531486572802102565352112548840783460445744423)}, {SC_(-0.25), SC_(11.75), SC_(-2980.9405282185801785979381426998934753615183894674)}, {SC_(-0.25), SC_(15.75), SC_(-9963.0984480949236929126495173451788015488533057312)}, {SC_(-0.25), SC_(19.75), SC_(-28354.285610765325603366060327671144508742992535586)},
      {SC_(3.75), SC_(-20.25), SC_(-0.0076845585942792341317694895749400053976192347461355)}, {SC_(3.75), SC_(-16.25), SC_(-0.026676473833363805218474733943073126852098252692238)}, {SC_(3.75), SC_(-12.25), SC_(-0.033150612620140155332437908902071743835476014605824)}, {SC_(3.75), SC_(-8.25), SC_(0.024862128358835876745073743789586165594233386818764)}, {SC_(3.75), SC_(-4.25), SC_(0.26643741037095553396026886662906805496932883791011)}, {SC_(3.75), SC_(-0.25), SC_(0.93506252732788015337201598317744583689077922422313)}, {SC_(3.75), SC_(3.75), SC_(2.4937080902782278272865074460355462658482459750891)}, {SC_(3.75), SC_(7.75), SC_(5.7782165977734310384947791703219081203794593104898)}, {SC_(3.75), SC_(11.75), SC_(12.239149970819448162027824359733914867194838641207)}, {SC_(3.75), SC_(15.75), SC_(24.315766317657856526802495882902104213004243807834)}, {SC_(3.75), SC_(19.75), SC_(46.004706133409223855903017790328079349160741103989)},
      {SC_(7.75), SC_(-20.25), SC_(0.037235565108204273745081008045192031428127589963378)}, {SC_(7.75), SC_(-16.25), SC_(0.084729597975458928169783385558211341184710436894527)}, {SC_(7.75), SC_(-12.25), SC_(0.17080635394402470513520780978929502652414093665998)}, {SC_(7.75), SC_(-8.25), SC_(0.31950343789501896907243089625679164966361926427901)}, {SC_(7.75), SC_(-4.25), SC_(0.56722331717592488544254097481360697514802761113579)}, {SC_(7.75), SC_(-0.25), SC_(0.96819884906571311048909491350402784950555589172778)}, {SC_(7.75), SC_(3.75), SC_(1.6020878195055145404559679357988911544832570195929)}, {SC_(7.75), SC_(7.75), SC_(2.5844402449306647890994627013439918401353618660618)}, {SC_(7.75), SC_(11.75), SC_(4.0810182332680718846036289812422612468750062913766)}, {SC_(7.75), SC_(15.75), SC_(6.3272529834696435764802870864047851742114357592781)}, {SC_(7.75), SC_(19.75), SC_(9.6545155398613375064364794042284225393502577025757)},
      {SC_(11.75), SC_(-20.25), SC_(0.15486394311085924113988037667235580632108514049961)}, {SC_(11.75), SC_(-16.25), SC_(0.22985383829087750746997781544418442650948306731355)}, {SC_(11.75), SC_(-12.25), SC_(0.33615798547981440387258985310070073263439571574352)}, {SC_(11.75), SC_(-8.25), SC_(0.48533791924865732402484841770387435054807176843922)}, {SC_(11.75), SC_(-4.25), SC_(0.69279476096089396016927378719976382816612949045723)}, {SC_(11.75), SC_(-0.25), SC_(0.97893073946457038719047235276954159274687951133239)}, {SC_(11.75), SC_(3.75), SC_(1.3706338991326610410785896448412400026741719976537)}, {SC_(11.75), SC_(7.75), SC_(1.9031693475249062854591923959807180024296317864633)}, {SC_(11.75), SC_(11.75), SC_(2.6225804467534900775963810848242641845248345641566)}, {SC_(11.75), SC_(15.75), SC_(3.5887279276489256865660553406508246843289687389280)}, {SC_(11.75), SC_(19.75), SC_(4.8791249650630001302695046693426702384634788655376)},
      {SC_(15.75), SC_(-20.25), SC_(0.26169993773941504714021934731773052404003435302548)}, {SC_(15.75), SC_(-16.25), SC_(0.34428767856756521281521994646213632566799672170823)}, {SC_(15.75), SC_(-12.25), SC_(0.45068705303931291468643647219845752956581924151602)}, {SC_(15.75), SC_(-8.25), SC_(0.58722904807165396939912732843015800226017006383889)}, {SC_(15.75), SC_(-4.25), SC_(0.76180845119510741657129800934863890343557924548267)}, {SC_(15.75), SC_(-0.25), SC_(0.98424488519002985986673227194811800795924545598747)}, {SC_(15.75), SC_(3.75), SC_(1.2667221438640806060367418270328561473306297946124)}, {SC_(15.75), SC_(7.75), SC_(1.6243218504073229104605986746109545497016155557456)}, {SC_(15.75), SC_(11.75), SC_(2.0756705639798239579947551789739745396066053149652)}, {SC_(15.75), SC_(15.75), SC_(2.6437231357748258767712950042187028922110335308912)}, {SC_(15.75), SC_(19.75), SC_(3.3567094629489291868172072628630988653584236011026)},
      {SC_(19.75), SC_(-20.25), SC_(0.34910186209886263988734004369646266800659689838760)}, {SC_(19.75), SC_(-16.25), SC_(0.43171851514846723176830271990344447636246814031258)}, {SC_(19.75), SC_(-12.25), SC_(0.53264760691226214051563276361223610040193575209722)}, {SC_(19.75), SC_(-8.25), SC_(0.65570932018638949205413006445398352201545799769694)}, {SC_(19.75), SC_(-4.25), SC_(0.80547695536244789152425915957330496255335464733020)}, {SC_(19.75), SC_(-0.25), SC_(0.98741773517508964436868231216434995093107999788450)}, {SC_(19.75), SC_(3.75), SC_(1.2080586524527299846909832323308446155063281314444)}, {SC_(19.75), SC_(7.75), SC_(1.4751816095060559707610879513647971547078203326785)}, {SC_(19.75), SC_(11.75), SC_(1.7980527870029919079278807774802021351478928537606)}, {SC_(19.75), SC_(15.75), SC_(2.1876919765295108137252526717389200156554872202073)}, {SC_(19.75), SC_(19.75), SC_(2.6571885305131654484163938203293169727636168525176)}
      } };

   static const std::array<std::array<T, 3>, 49> hypergeometric_0F1_large_data = { {
      {SC_(-3000.25), SC_(-3000.25), SC_(2.7187352281773126038196142076996225709478475910049)},
      {SC_(-3000.25), SC_(-2000.25), SC_(1.9479325178881941977364868969702984561194629278005)},
      {SC_(-3000.25), SC_(-1000.25), SC_(1.3957158200680510708579318399559946925035296441969)},
      {SC_(-3000.25), SC_(-0.25), SC_(1.0000833298623651641409421309527751141654844918029)},
      {SC_(-3000.25), SC_(999.75), SC_(0.71662418615385142079900540026845986168175943851435)},
      {SC_(-3000.25), SC_(1999.75), SC_(0.51352644595687380807192108174566627121840655509659)},
      {SC_(-3000.25), SC_(2999.75), SC_(0.36800205062066223494767361354167341477112311421338)},
      {SC_(-2000.25), SC_(-3000.25), SC_(4.4839337747691491664160512023395421809359987226033)},
      {SC_(-2000.25), SC_(-2000.25), SC_(2.7189621930215506574513067999560632490479415009312)},
      {SC_(-2000.25), SC_(-1000.25), SC_(1.6489274597179783576990334595113842446837612984637)},
      {SC_(-2000.25), SC_(-0.25), SC_(1.0001249921917327582862611787131655498347374570534)},
      {SC_(-2000.25), SC_(999.75), SC_(0.60668227026545158239160396829655637629150925375338)},
      {SC_(-2000.25), SC_(1999.75), SC_(0.36806334257221693918034782383378883527025156371561)},
      {SC_(-2000.25), SC_(2999.75), SC_(0.22332534501129284494390126255673652609551748168190)},
      {SC_(-1000.25), SC_(-3000.25), SC_(20.166446124477887217071731764646075153043381039788)},
      {SC_(-1000.25), SC_(-2000.25), SC_(7.4020458503369278169047297486603438977667911685454)},
      {SC_(-1000.25), SC_(-1000.25), SC_(2.7196441509079794494949614854599837302121989306579)},
      {SC_(-1000.25), SC_(-0.25), SC_(1.0002499687838699774154682651484339556685615759685)},
      {SC_(-1000.25), SC_(999.75), SC_(0.36824716733727347121444226394598870471042459648225)},
      {SC_(-1000.25), SC_(1999.75), SC_(0.13570722006231629831063556421918175042108431159794)},
      {SC_(-1000.25), SC_(2999.75), SC_(0.050060760590698310218753944980019339485378387824874)},
      {SC_(-0.25), SC_(-3000.25), SC_(39.685967392358901409909771219162599134220400862017)},
      {SC_(-0.25), SC_(-2000.25), SC_(42.589937906362216198404510603403791771675699582116)},
      {SC_(-0.25), SC_(-1000.25), SC_(1.4484609059158563254575589143006796017980497019204)},
      {SC_(-0.25), SC_(-0.25), SC_(1.8410918501257885334774939532672407660260932497146)},
      {SC_(-0.25), SC_(999.75), SC_(-5.3078213765443269585708737506907854937173735893125e28) },
      {SC_(-0.25), SC_(1999.75), SC_(-1.6498771472158460728992067699031965281087177690027e40) },
      {SC_(-0.25), SC_(2999.75), SC_(-1.0342523123207467753461742345710027886431938539942e49) },
      {SC_(999.75), SC_(-3000.25), SC_(0.049513102314849089089531272645546209356947364503693)}, {SC_(999.75), SC_(-2000.25), SC_(0.13496287555692361766808821455578584612232691847368)}, {SC_(999.75), SC_(-1000.25), SC_(0.36751140843960205420082946295266027163679747815171)}, {SC_(999.75), SC_(-0.25), SC_(0.99974996871616159816731662896550362438335384158579)}, {SC_(999.75), SC_(999.75), SC_(2.7169258487486599795213704968075693651612629011137)}, {SC_(999.75), SC_(1999.75), SC_(7.3761834991423536961023917193398034973414374920724)}, {SC_(999.75), SC_(2999.75), SC_(20.005752597249211333476751024563565243417014841294)},
      {SC_(1999.75), SC_(-3000.25), SC_(0.22293486720691878909733143630236248153349047769471)}, {SC_(1999.75), SC_(-2000.25), SC_(0.36769546312912945115503617374640562125026416585911)}, {SC_(1999.75), SC_(-1000.25), SC_(0.60637900493362087991135014744274427763909334895653)}, {SC_(1999.75), SC_(-0.25), SC_(0.99987499218326921518475889542511447173965188103381)}, {SC_(1999.75), SC_(999.75), SC_(1.6485152791856256326123376967789594359576461105786)}, {SC_(1999.75), SC_(1999.75), SC_(2.7176030495659989803962821602572269144434394541710)}, {SC_(1999.75), SC_(2999.75), SC_(4.4794520688544123057192034298995619570726142156707)},
      {SC_(2999.75), SC_(-3000.25), SC_(0.36775679765931355729803647936785321939707796855752)}, {SC_(2999.75), SC_(-2000.25), SC_(0.51330776829498225175667208437735196999610552588713)}, {SC_(2999.75), SC_(-1000.25), SC_(0.71643841877594009499597675075273584291266593195763)}, {SC_(2999.75), SC_(-0.25), SC_(0.99991666319319078123594326189204686183292938405581)}, {SC_(2999.75), SC_(999.75), SC_(1.3955090626492889292016427682906884819283986108381)}, {SC_(2999.75), SC_(1999.75), SC_(1.9475357570910758403975860806320078849962664462281)}, {SC_(2999.75), SC_(2999.75), SC_(2.7178291334815105222784044221313459883434486746788)},
   } };

   do_test_0F1<T>(hypergeometric_0F1_integer_data, type_name, "Integer Arguments");
   do_test_0F1<T>(hypergeometric_0F1_real_data, type_name, "Real Arguments");
   do_test_0F1<T>(hypergeometric_0F1_large_data, type_name, "Large Arguments");
}