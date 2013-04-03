<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="frames">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="A4L-LOC">
<wire x1="256.54" y1="3.81" x2="256.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="256.54" y1="8.89" x2="256.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="256.54" y1="13.97" x2="256.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="256.54" y1="19.05" x2="256.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="161.29" y1="3.81" x2="161.29" y2="24.13" width="0.1016" layer="94"/>
<wire x1="161.29" y1="24.13" x2="215.265" y2="24.13" width="0.1016" layer="94"/>
<wire x1="215.265" y1="24.13" x2="256.54" y2="24.13" width="0.1016" layer="94"/>
<wire x1="246.38" y1="3.81" x2="246.38" y2="8.89" width="0.1016" layer="94"/>
<wire x1="246.38" y1="8.89" x2="256.54" y2="8.89" width="0.1016" layer="94"/>
<wire x1="246.38" y1="8.89" x2="215.265" y2="8.89" width="0.1016" layer="94"/>
<wire x1="215.265" y1="8.89" x2="215.265" y2="3.81" width="0.1016" layer="94"/>
<wire x1="215.265" y1="8.89" x2="215.265" y2="13.97" width="0.1016" layer="94"/>
<wire x1="215.265" y1="13.97" x2="256.54" y2="13.97" width="0.1016" layer="94"/>
<wire x1="215.265" y1="13.97" x2="215.265" y2="19.05" width="0.1016" layer="94"/>
<wire x1="215.265" y1="19.05" x2="256.54" y2="19.05" width="0.1016" layer="94"/>
<wire x1="215.265" y1="19.05" x2="215.265" y2="24.13" width="0.1016" layer="94"/>
<text x="217.17" y="15.24" size="2.54" layer="94" font="vector">&gt;DRAWING_NAME</text>
<text x="217.17" y="10.16" size="2.286" layer="94" font="vector">&gt;LAST_DATE_TIME</text>
<text x="230.505" y="5.08" size="2.54" layer="94" font="vector">&gt;SHEET</text>
<text x="216.916" y="4.953" size="2.54" layer="94" font="vector">Sheet:</text>
<frame x1="0" y1="0" x2="260.35" y2="179.07" columns="6" rows="4" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="A4L-LOC" prefix="FRAME" uservalue="yes">
<description>&lt;b&gt;FRAME&lt;/b&gt;&lt;p&gt;
DIN A4, landscape with location and doc. field</description>
<gates>
<gate name="G$1" symbol="A4L-LOC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="RaspberryPi2">
<packages>
<package name="RASPBERRY-PI_REV2_BLABOT">
<wire x1="85" y1="56" x2="0" y2="56" width="0.127" layer="51"/>
<wire x1="0" y1="56" x2="0" y2="44.5" width="0.127" layer="51"/>
<wire x1="0" y1="16.7" x2="0" y2="0" width="0.127" layer="51"/>
<wire x1="0" y1="0" x2="85" y2="0" width="0.127" layer="51"/>
<wire x1="85" y1="0" x2="85" y2="56" width="0.127" layer="51"/>
<wire x1="1.475" y1="51.65" x2="3.325" y2="51.65" width="0.127" layer="21"/>
<wire x1="3.325" y1="51.65" x2="3.325" y2="49.8" width="0.127" layer="21" curve="1.965897"/>
<wire x1="3.325" y1="49.8" x2="1.475" y2="49.8" width="0.127" layer="21"/>
<wire x1="1.475" y1="49.8" x2="1.475" y2="51.65" width="0.127" layer="21"/>
<wire x1="0" y1="44.5" x2="19" y2="44.5" width="0.127" layer="51"/>
<wire x1="19" y1="44.5" x2="19" y2="16.7" width="0.127" layer="51"/>
<wire x1="19" y1="16.7" x2="0" y2="16.7" width="0.127" layer="51"/>
<wire x1="0" y1="16.7" x2="0" y2="44.5" width="0.127" layer="51"/>
<wire x1="75.5" y1="37.2" x2="92.7" y2="37.2" width="0.127" layer="51"/>
<wire x1="92.7" y1="37.2" x2="92.7" y2="23.95" width="0.127" layer="51"/>
<wire x1="92.7" y1="23.95" x2="75.5" y2="23.95" width="0.127" layer="51"/>
<wire x1="75.5" y1="23.95" x2="75.5" y2="37.2" width="0.127" layer="51"/>
<wire x1="64.2" y1="2" x2="86" y2="2" width="0.127" layer="51"/>
<wire x1="86" y1="2" x2="86" y2="17.4" width="0.127" layer="51"/>
<wire x1="86" y1="17.4" x2="64.2" y2="17.4" width="0.127" layer="51"/>
<wire x1="64.2" y1="17.4" x2="64.2" y2="2" width="0.127" layer="51"/>
<wire x1="5.1" y1="3.625" x2="-0.5" y2="3.625" width="0.127" layer="51"/>
<wire x1="-0.5" y1="3.625" x2="-0.5" y2="11.225" width="0.127" layer="51"/>
<wire x1="-0.5" y1="11.225" x2="5.1" y2="11.225" width="0.127" layer="51"/>
<wire x1="5.1" y1="11.225" x2="5.1" y2="3.625" width="0.127" layer="51"/>
<wire x1="1" y1="49.5" x2="34.2" y2="49.5" width="0.127" layer="21"/>
<wire x1="34.2" y1="49.5" x2="34.2" y2="54.5" width="0.127" layer="21"/>
<wire x1="34.2" y1="54.5" x2="1" y2="54.5" width="0.127" layer="21"/>
<wire x1="1" y1="54.5" x2="1" y2="49.5" width="0.127" layer="21"/>
<wire x1="0" y1="44.5" x2="-15" y2="44.5" width="0.05" layer="51"/>
<wire x1="-15" y1="44.5" x2="-15" y2="16.7" width="0.05" layer="51"/>
<wire x1="-15" y1="16.7" x2="0.1" y2="16.7" width="0.05" layer="51"/>
<wire x1="0.1" y1="16.7" x2="0.1" y2="16.6" width="0.05" layer="51"/>
<wire x1="41.01" y1="53.885" x2="41.01" y2="62.185" width="0.127" layer="51"/>
<wire x1="41.01" y1="62.185" x2="49.91" y2="62.085" width="0.127" layer="51"/>
<wire x1="49.91" y1="62.085" x2="49.91" y2="53.785" width="0.127" layer="51"/>
<wire x1="49.91" y1="53.785" x2="40.62" y2="53.885" width="0.127" layer="51"/>
<wire x1="40.57" y1="43.875" x2="50.37" y2="43.775" width="0.127" layer="51"/>
<wire x1="50.37" y1="43.775" x2="50.37" y2="53.775" width="0.127" layer="51"/>
<wire x1="50.37" y1="53.775" x2="40.57" y2="53.875" width="0.127" layer="51"/>
<wire x1="40.57" y1="53.875" x2="40.57" y2="43.875" width="0.127" layer="51"/>
<wire x1="71" y1="56.025" x2="71" y2="44.625" width="0.127" layer="51"/>
<wire x1="71" y1="44.625" x2="59" y2="44.625" width="0.127" layer="51"/>
<wire x1="59" y1="44.625" x2="59" y2="56.025" width="0.127" layer="51"/>
<wire x1="68.3" y1="56.025" x2="68.4" y2="56.025" width="0.127" layer="51"/>
<wire x1="68.4" y1="56.025" x2="68.4" y2="59.625" width="0.127" layer="51"/>
<wire x1="68.4" y1="59.625" x2="61.8" y2="59.625" width="0.127" layer="51"/>
<wire x1="61.8" y1="59.625" x2="61.8" y2="56.025" width="0.127" layer="51"/>
<wire x1="37.5" y1="-1.175" x2="52.6" y2="-1.175" width="0.127" layer="51"/>
<wire x1="52.6" y1="-1.175" x2="52.6" y2="10.225" width="0.127" layer="51"/>
<wire x1="52.6" y1="10.225" x2="37.5" y2="10.225" width="0.127" layer="51"/>
<wire x1="37.5" y1="10.225" x2="37.5" y2="-1.175" width="0.127" layer="51"/>
<pad name="P1_1" x="2.4" y="50.725" drill="1" shape="square"/>
<pad name="P1_2" x="2.4" y="53.265" drill="1" diameter="1.6764"/>
<pad name="P1_3" x="4.94" y="50.725" drill="1"/>
<pad name="P1_4" x="4.94" y="53.265" drill="1"/>
<pad name="P1_5" x="7.48" y="50.725" drill="1"/>
<pad name="P1_6" x="7.48" y="53.265" drill="1" diameter="1.6764"/>
<pad name="P1_7" x="10.02" y="50.725" drill="1"/>
<pad name="P1_8" x="10.02" y="53.265" drill="1"/>
<pad name="P1_9" x="12.56" y="50.725" drill="1"/>
<pad name="P1_10" x="12.56" y="53.265" drill="1"/>
<pad name="P1_11" x="15.1" y="50.725" drill="1"/>
<pad name="P1_12" x="15.1" y="53.265" drill="1"/>
<pad name="P1_13" x="17.64" y="50.725" drill="1"/>
<pad name="P1_14" x="17.64" y="53.265" drill="1"/>
<pad name="P1_15" x="20.18" y="50.725" drill="1"/>
<pad name="P1_16" x="20.18" y="53.265" drill="1"/>
<pad name="P1_17" x="22.72" y="50.725" drill="1"/>
<pad name="P1_18" x="22.72" y="53.265" drill="1"/>
<pad name="P1_19" x="25.26" y="50.725" drill="1"/>
<pad name="P1_20" x="25.26" y="53.265" drill="1"/>
<pad name="P1_21" x="27.8" y="50.725" drill="1"/>
<pad name="P1_22" x="27.8" y="53.265" drill="1"/>
<pad name="P1_23" x="30.34" y="50.725" drill="1"/>
<pad name="P1_24" x="30.34" y="53.265" drill="1"/>
<pad name="P1_25" x="32.88" y="50.725" drill="1"/>
<pad name="P1_26" x="32.88" y="53.265" drill="1"/>
<text x="10.18" y="57.535" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="36.4" y="54.225" size="1.27" layer="21" ratio="10" rot="R180">26</text>
<text x="10.015" y="55.63" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="10.1286" y="26.3289" size="1.27" layer="51" rot="R90">SD Card </text>
<text x="1.9036" y="49.0289" size="0.4064" layer="51">3v3</text>
<text x="2.0286" y="54.6539" size="0.4064" layer="51">5v</text>
<text x="6.6786" y="54.6039" size="0.4064" layer="51">GND</text>
<text x="90.09" y="28.675" size="1.27" layer="51" rot="R90">USB</text>
<text x="83.64" y="8.575" size="1.27" layer="51" rot="R90">RJ45</text>
<text x="2.615" y="4.3" size="1.27" layer="51" rot="R90">usb +5V</text>
<text x="14.9" y="18.5" size="1.27" layer="51" rot="R90">SD card holder 5mm bottom sick</text>
<text x="36.4" y="51.225" size="1.27" layer="21" ratio="10" rot="R180">25</text>
<text x="36.8" y="28.325" size="1.27" layer="51">Board 56x85mm H=16mm</text>
<text x="62.75" y="53.2" size="1.27" layer="51">Audio</text>
<text x="43.6" y="51.875" size="1.27" layer="51">RCA</text>
<text x="42.375" y="3.8" size="1.27" layer="51">HDMI</text>
<rectangle x1="2.146" y1="53.011" x2="2.654" y2="53.519" layer="51"/>
<rectangle x1="4.686" y1="53.011" x2="5.194" y2="53.519" layer="51"/>
<rectangle x1="7.226" y1="53.011" x2="7.734" y2="53.519" layer="51"/>
<rectangle x1="9.766" y1="53.011" x2="10.274" y2="53.519" layer="51"/>
<rectangle x1="12.306" y1="53.011" x2="12.814" y2="53.519" layer="51" rot="R90"/>
<rectangle x1="14.846" y1="53.011" x2="15.354" y2="53.519" layer="51"/>
<rectangle x1="17.386" y1="53.011" x2="17.894" y2="53.519" layer="51"/>
<rectangle x1="19.926" y1="53.011" x2="20.434" y2="53.519" layer="51"/>
<rectangle x1="22.466" y1="53.011" x2="22.974" y2="53.519" layer="51"/>
<rectangle x1="25.006" y1="53.011" x2="25.514" y2="53.519" layer="51"/>
<rectangle x1="27.546" y1="53.011" x2="28.054" y2="53.519" layer="51"/>
<rectangle x1="30.086" y1="53.011" x2="30.594" y2="53.519" layer="51"/>
<rectangle x1="32.626" y1="53.011" x2="33.134" y2="53.519" layer="51"/>
<rectangle x1="2.146" y1="50.471" x2="2.654" y2="50.979" layer="51"/>
<rectangle x1="4.686" y1="50.471" x2="5.194" y2="50.979" layer="51"/>
<rectangle x1="7.226" y1="50.471" x2="7.734" y2="50.979" layer="51"/>
<rectangle x1="9.766" y1="50.471" x2="10.274" y2="50.979" layer="51"/>
<rectangle x1="12.306" y1="50.471" x2="12.814" y2="50.979" layer="51"/>
<rectangle x1="14.846" y1="50.471" x2="15.354" y2="50.979" layer="51"/>
<rectangle x1="17.386" y1="50.471" x2="17.894" y2="50.979" layer="51"/>
<rectangle x1="19.926" y1="50.471" x2="20.434" y2="50.979" layer="51"/>
<rectangle x1="22.466" y1="50.471" x2="22.974" y2="50.979" layer="51"/>
<rectangle x1="25.006" y1="50.471" x2="25.514" y2="50.979" layer="51"/>
<rectangle x1="27.546" y1="50.471" x2="28.054" y2="50.979" layer="51"/>
<rectangle x1="30.086" y1="50.471" x2="30.594" y2="50.979" layer="51"/>
<rectangle x1="32.626" y1="50.471" x2="33.134" y2="50.979" layer="51"/>
<hole x="80" y="43.5" drill="2.9"/>
<hole x="25.5" y="18" drill="2.9"/>
<wire x1="26.575" y1="3.425" x2="28.425" y2="3.425" width="0.127" layer="21"/>
<wire x1="28.425" y1="3.425" x2="28.425" y2="1.575" width="0.127" layer="21" curve="1.965897"/>
<wire x1="28.425" y1="1.575" x2="26.575" y2="1.575" width="0.127" layer="21"/>
<wire x1="26.575" y1="1.575" x2="26.575" y2="3.425" width="0.127" layer="21"/>
<pad name="P6_1" x="27.5" y="2.5" drill="1" shape="square"/>
<pad name="P6_2" x="27.5" y="5.04" drill="1" diameter="1.6764"/>
<rectangle x1="27.246" y1="4.786" x2="27.754" y2="5.294" layer="51"/>
<rectangle x1="27.246" y1="2.246" x2="27.754" y2="2.754" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="RASPBERRY-PI_REV2_BLABOT">
<wire x1="-45.72" y1="48.26" x2="0" y2="48.26" width="0.254" layer="94"/>
<wire x1="0" y1="48.26" x2="0" y2="12.7" width="0.254" layer="94"/>
<wire x1="0" y1="12.7" x2="-45.72" y2="12.7" width="0.254" layer="94"/>
<wire x1="-45.72" y1="12.7" x2="-45.72" y2="48.26" width="0.254" layer="94"/>
<wire x1="-45.72" y1="12.7" x2="-45.72" y2="7.62" width="0.254" layer="94"/>
<wire x1="-45.72" y1="7.62" x2="0" y2="7.62" width="0.254" layer="94"/>
<wire x1="0" y1="7.62" x2="0" y2="12.7" width="0.254" layer="94"/>
<text x="-45.72" y="48.768" size="1.27" layer="95">&gt;NAME</text>
<text x="0" y="6.858" size="1.27" layer="96" rot="R180">&gt;VALUE</text>
<text x="-22.86" y="30.48" size="1.27" layer="94">P1</text>
<text x="-22.86" y="10.16" size="1.27" layer="94">P6</text>
<pin name="5V@2" x="5.08" y="45.72" length="middle" rot="R180"/>
<pin name="5V@4" x="5.08" y="43.18" length="middle" rot="R180"/>
<pin name="GND@6" x="5.08" y="40.64" length="middle" rot="R180"/>
<pin name="GPIO14,UART0_TXD" x="5.08" y="38.1" length="middle" rot="R180"/>
<pin name="GPIO15,UART0_RXD" x="5.08" y="35.56" length="middle" rot="R180"/>
<pin name="GPIO18" x="5.08" y="33.02" length="middle" rot="R180"/>
<pin name="GND@14" x="5.08" y="30.48" length="middle" rot="R180"/>
<pin name="GPIO23" x="5.08" y="27.94" length="middle" rot="R180"/>
<pin name="GPIO24" x="5.08" y="25.4" length="middle" rot="R180"/>
<pin name="GND@20" x="5.08" y="22.86" length="middle" rot="R180"/>
<pin name="GPIO25" x="5.08" y="20.32" length="middle" rot="R180"/>
<pin name="GPIO8,SPI0_CE0" x="5.08" y="17.78" length="middle" rot="R180"/>
<pin name="GPIO7,SPI0_CE1" x="5.08" y="15.24" length="middle" rot="R180"/>
<pin name="3V3@1" x="-50.8" y="45.72" length="middle"/>
<pin name="GPIO2,I2C0_SDA" x="-50.8" y="43.18" length="middle"/>
<pin name="GPIO3,I2C0_SCL" x="-50.8" y="40.64" length="middle"/>
<pin name="GPIO4,GPCLK0" x="-50.8" y="38.1" length="middle"/>
<pin name="GND@9" x="-50.8" y="35.56" length="middle"/>
<pin name="GPIO17" x="-50.8" y="33.02" length="middle"/>
<pin name="GPIO27" x="-50.8" y="30.48" length="middle"/>
<pin name="GPIO22" x="-50.8" y="27.94" length="middle"/>
<pin name="3V3@17" x="-50.8" y="25.4" length="middle"/>
<pin name="GPIO10_MOSI" x="-50.8" y="22.86" length="middle"/>
<pin name="GPIO9_MISO" x="-50.8" y="20.32" length="middle"/>
<pin name="GPIO11_SCLK" x="-50.8" y="17.78" length="middle"/>
<pin name="GND@25" x="-50.8" y="15.24" length="middle"/>
<pin name="RUN" x="-50.8" y="10.16" length="middle"/>
<pin name="GND@P6_2" x="5.08" y="10.16" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="RASPBERRY-PI_REV2_BLABOT">
<gates>
<gate name="G$1" symbol="RASPBERRY-PI_REV2_BLABOT" x="0" y="-7.62"/>
</gates>
<devices>
<device name="RASPBERRY-PI_REV2_BLABOT" package="RASPBERRY-PI_REV2_BLABOT">
<connects>
<connect gate="G$1" pin="3V3@1" pad="P1_1"/>
<connect gate="G$1" pin="3V3@17" pad="P1_17"/>
<connect gate="G$1" pin="5V@2" pad="P1_2"/>
<connect gate="G$1" pin="5V@4" pad="P1_4"/>
<connect gate="G$1" pin="GND@14" pad="P1_14"/>
<connect gate="G$1" pin="GND@20" pad="P1_20"/>
<connect gate="G$1" pin="GND@25" pad="P1_25"/>
<connect gate="G$1" pin="GND@6" pad="P1_6"/>
<connect gate="G$1" pin="GND@9" pad="P1_9"/>
<connect gate="G$1" pin="GND@P6_2" pad="P6_2"/>
<connect gate="G$1" pin="GPIO10_MOSI" pad="P1_19"/>
<connect gate="G$1" pin="GPIO11_SCLK" pad="P1_23"/>
<connect gate="G$1" pin="GPIO14,UART0_TXD" pad="P1_8"/>
<connect gate="G$1" pin="GPIO15,UART0_RXD" pad="P1_10"/>
<connect gate="G$1" pin="GPIO17" pad="P1_11"/>
<connect gate="G$1" pin="GPIO18" pad="P1_12"/>
<connect gate="G$1" pin="GPIO2,I2C0_SDA" pad="P1_3"/>
<connect gate="G$1" pin="GPIO22" pad="P1_15"/>
<connect gate="G$1" pin="GPIO23" pad="P1_16"/>
<connect gate="G$1" pin="GPIO24" pad="P1_18"/>
<connect gate="G$1" pin="GPIO25" pad="P1_22"/>
<connect gate="G$1" pin="GPIO27" pad="P1_13"/>
<connect gate="G$1" pin="GPIO3,I2C0_SCL" pad="P1_5"/>
<connect gate="G$1" pin="GPIO4,GPCLK0" pad="P1_7"/>
<connect gate="G$1" pin="GPIO7,SPI0_CE1" pad="P1_26"/>
<connect gate="G$1" pin="GPIO8,SPI0_CE0" pad="P1_24"/>
<connect gate="G$1" pin="GPIO9_MISO" pad="P1_21"/>
<connect gate="G$1" pin="RUN" pad="P6_1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="jst">
<packages>
<package name="B4B-ZR">
<description>&lt;b&gt;ZH CONNECTOR&lt;/b&gt;  Top entry type, 1.5 mm, 4 pin 1 row&lt;p&gt;
Source: http://www.jst.com .. eZH.pdf</description>
<wire x1="0" y1="0.07" x2="7.5" y2="0.07" width="0.127" layer="21"/>
<wire x1="7.5" y1="0.07" x2="7.5" y2="-3.43" width="0.127" layer="21"/>
<wire x1="7.5" y1="-3.43" x2="0" y2="-3.43" width="0.127" layer="21"/>
<wire x1="0" y1="-3.43" x2="0" y2="0.07" width="0.127" layer="21"/>
<text x="-0.75" y="0.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.75" y="-5.365" size="1.27" layer="27">&gt;VALUE</text>
<pad name="4" x="1.5" y="-1.3" drill="0.7"/>
<pad name="3" x="3" y="-1.3" drill="0.7"/>
<pad name="2" x="4.5" y="-1.3" drill="0.7"/>
<pad name="1" x="6" y="-1.3" drill="0.7"/>
</package>
<package name="B5B-ZR">
<wire x1="0" y1="0.07" x2="9" y2="0.07" width="0.127" layer="21"/>
<wire x1="9" y1="0.07" x2="9" y2="-3.43" width="0.127" layer="21"/>
<wire x1="9" y1="-3.43" x2="0" y2="-3.43" width="0.127" layer="21"/>
<wire x1="0" y1="-3.43" x2="0" y2="0.07" width="0.127" layer="21"/>
<text x="-0.75" y="0.27" size="1.27" layer="25">&gt;NAME</text>
<text x="-0.75" y="-5.365" size="1.27" layer="27">&gt;VALUE</text>
<pad name="5" x="1.5" y="-1.3" drill="0.7"/>
<pad name="4" x="3" y="-1.3" drill="0.7"/>
<pad name="3" x="4.5" y="-1.3" drill="0.7"/>
<pad name="2" x="6" y="-1.3" drill="0.7"/>
<pad name="1" x="7.5" y="-1.3" drill="0.7"/>
</package>
</packages>
<symbols>
<symbol name="B4B-ZR">
<pin name="1" x="-7.62" y="2.54" visible="pin" length="middle"/>
<pin name="2" x="-7.62" y="0" visible="pin" length="middle"/>
<pin name="3" x="-7.62" y="-2.54" visible="pin" length="middle"/>
<pin name="4" x="-7.62" y="-5.08" visible="pin" length="middle"/>
<text x="-2.54" y="5.842" size="1.27" layer="95">&gt;NAME</text>
<text x="-2.54" y="-9.398" size="1.27" layer="96">&gt;VALUE</text>
<wire x1="-5.08" y1="5.08" x2="2.54" y2="5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="-7.62" width="0.254" layer="94"/>
<wire x1="2.54" y1="-7.62" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<circle x="-2.54" y="2.54" radius="0.915809375" width="0.254" layer="94"/>
<circle x="-2.54" y="0" radius="0.915809375" width="0.254" layer="94"/>
<circle x="-2.54" y="-2.54" radius="0.915809375" width="0.254" layer="94"/>
<circle x="-2.54" y="-5.08" radius="0.915809375" width="0.254" layer="94"/>
</symbol>
<symbol name="B5B-ZR">
<pin name="1" x="-7.62" y="5.08" visible="pin" length="middle"/>
<pin name="2" x="-7.62" y="2.54" visible="pin" length="middle"/>
<pin name="3" x="-7.62" y="0" visible="pin" length="middle"/>
<pin name="4" x="-7.62" y="-2.54" visible="pin" length="middle"/>
<pin name="5" x="-7.62" y="-5.08" visible="pin" length="middle"/>
<text x="-2.54" y="8.382" size="1.27" layer="95">&gt;NAME</text>
<text x="-2.54" y="-9.398" size="1.27" layer="96">&gt;VALUE</text>
<wire x1="-5.08" y1="7.62" x2="2.54" y2="7.62" width="0.254" layer="94"/>
<wire x1="2.54" y1="7.62" x2="2.54" y2="-7.62" width="0.254" layer="94"/>
<wire x1="2.54" y1="-7.62" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<circle x="-2.54" y="5.08" radius="0.915809375" width="0.254" layer="94"/>
<circle x="-2.54" y="2.54" radius="0.915809375" width="0.254" layer="94"/>
<circle x="-2.54" y="0" radius="0.915809375" width="0.254" layer="94"/>
<circle x="-2.54" y="-2.54" radius="0.915809375" width="0.254" layer="94"/>
<circle x="-2.54" y="-5.08" radius="0.915809375" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="B4B-ZR" prefix="CON">
<description>&lt;b&gt;JST-ZH Connector&lt;/b&gt;&lt;br&gt;
4 pol, 1.5mm pitch&lt;br&gt;
Package: &lt;b&gt;B4B-ZR&lt;/b&gt;
&lt;br&gt;&lt;br&gt;
Source: &lt;a href="http://www.jst-mfg.com/product/pdf/eng/eZH.pdf"&gt;http://www.jst-mfg.com/product/pdf/eng/eZH.pdf&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="B4B-ZR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="B4B-ZR">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="B5B-ZR">
<description>&lt;b&gt;JST-ZH Connector&lt;/b&gt;&lt;br&gt;
5 pol, 1.5mm pitch&lt;br&gt;
Package: &lt;b&gt;B5B-ZR&lt;/b&gt;
&lt;br&gt;&lt;br&gt;
Source: &lt;a href="http://www.jst-mfg.com/product/pdf/eng/eZH.pdf"&gt;http://www.jst-mfg.com/product/pdf/eng/eZH.pdf&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="B5B-ZR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="B5B-ZR">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="frames" deviceset="A4L-LOC" device=""/>
<part name="U$1" library="RaspberryPi2" deviceset="RASPBERRY-PI_REV2_BLABOT" device="RASPBERRY-PI_REV2_BLABOT"/>
<part name="CON1" library="jst" deviceset="B4B-ZR" device=""/>
<part name="CON2" library="jst" deviceset="B4B-ZR" device=""/>
<part name="CON3" library="jst" deviceset="B4B-ZR" device=""/>
<part name="CON4" library="jst" deviceset="B4B-ZR" device=""/>
<part name="U$2" library="jst" deviceset="B5B-ZR" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="FRAME1" gate="G$1" x="0" y="0"/>
<instance part="U$1" gate="G$1" x="127" y="104.14"/>
<instance part="CON1" gate="G$1" x="40.64" y="129.54"/>
<instance part="CON2" gate="G$1" x="40.64" y="111.76"/>
<instance part="CON3" gate="G$1" x="40.64" y="93.98"/>
<instance part="CON4" gate="G$1" x="40.64" y="76.2"/>
<instance part="U$2" gate="G$1" x="40.64" y="55.88"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
