#!/usr/bin/perl -w

use strict;
use HTML::Entities qw(decode_entities);
use HTML::TableExtract;
require HTTP::Request;
require LWP::UserAgent;

sub trim {
	@_ = $_ if not @_ and defined wantarray;
	@_ = @_ if defined wantarray;
	for (@_ ? @_ : $_) {
		if (defined $_) {
			s/\xC2\xA0//;
			s/\x96/-/g;
			s/^[“\s]+//;
			s/[-”\s]+$//;
			s/^\((.*)\)$/$1/;
			s/"/\\"/g;
		}
	}
	return wantarray ? @_ : $_[0] if defined wantarray;
}

sub fetch {
	my $type = shift;
	my $req = HTTP::Request->new(GET => "http://www.dvb.org/products_registration/dvb_identifiers/identifiers.xml?type=" . $type);
	#my $req = HTTP::Request->new(GET => "file:" . $type . ".html");
	my $ua = LWP::UserAgent->new;
	my $rsp = $ua->request($req);
	die $rsp->status_line unless ($rsp->is_success);
	return decode_entities($rsp->decoded_content);
}

sub parse_table {
	my $type = shift;
	my $page = fetch($type);
	my $te = HTML::TableExtract->new( headers => [ "ID/Range", @_ ] );
	$te->parse($page);
	# don't know the correct syntax to return the first element
	foreach my $ts ($te->tables) {
		return $ts;
	}
}

sub update {
	my $t = parse_table(@_);
	open(OUT, ">src/strings/identifiers/" . $_[0] . ".h");
	binmode(OUT, ":encoding(utf8)");
	foreach my $row ($t->rows) {
		my ($id, @fields) = trim @$row;
		$id =~ s/\s//g;
		if ($id =~ m/(0x[0-9a-fA-F]+)-(0x[0-9a-fA-F]+)/) {
			if (oct($2) < oct($1)) {
				print OUT "//";
			}
			print OUT "{ $1, $2, \"";
		} else {
			print OUT "{ $id, $id, \"";
		}
		for my $i (0 ... @fields - 1) {
			if (defined $fields[$i]) {
				print OUT $fields[$i];
				$i++;
				if (($i < @fields) and (defined $fields[$i])) {
					print OUT " | ";
				}
			} else {
				$i++;
			}
		}
		print OUT "\" },\n";
	}
	print OUT "{ 0, 0, NULL }\n";

	close(OUT);
}

sub bouquetID {
	update("bouquetID", "Name", "Country Code", "Operator");
}

sub caSystemID {
	update("caSystemID", "CA System specifier");
}

sub cpSystemID {
	update("cpSystemID", "CP System specifier");
}

sub dataBroadcastID {
	update("dataBroadcastID", "Data Broqadcast Specification Name");
}

sub networkID {
	update("networkID", "Description", "Country Code", "Network Type", "Operator");
}

sub originalNetworkID {
	update("originalNetworkID", "Description", "Operator");
}

sub privateDataSpecifierID {
	update("privateDataSpecifierID", "Organisation");
}

sub platformID {
	update("platformID", "Platform Name", "Operator");
}

sub rootOfTrustID {
	update("rootOfTrustID", "Description", "Operator");
}

sub mhpOrganisationID {
	update("mhpOrganisationID", "Organisation Supplying MHP Applications");
}

sub mhpApplicationTypeID {
	update("mhpApplicationTypeID", "Description", "Operator");
}

sub mhpAITDescriptors {
	update("mhpAITDescriptors", "Description", "Operator");
}

sub mhpProtocolID {
	update("mhpProtocolID", "Description");
}

# DVB-SI Identifiers
bouquetID();
caSystemID();
cpSystemID();
dataBroadcastID();
networkID();
originalNetworkID();
privateDataSpecifierID();
platformID();
rootOfTrustID();

# MHP Identifiers
mhpOrganisationID();
mhpApplicationTypeID();
mhpAITDescriptors();
mhpProtocolID();

