/*
    PSEntry.h
    PubSub

    Copyright 2006, Apple Computer, Inc.  All rights reserved.
*/


#import <Foundation/NSObject.h>
@class NSArray;
@class NSString;
@class NSDate;
@class NSTimeZone;
@class NSURL;
@class NSXMLElement;


#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class PSFeed;
@class PSContent;


/*!
    @class      PSEntry
    @discussion A <code>PSEntry</code> is an entry in a feed object. Entry objects are acquired from the
                associated feed object.
				
                Most of the attributes for an entry are defined by the RSS 2.0 and Atom 1.0 specs.
                Any attributes defined by those specs (or nonstandard extensions) that are not
                natively supported by PSEntry can be retrieved from the entry objects' <code>XMLRepresentation</code> property.

                Some <code>PSEntry</code> attributes are specific to the local copy of the entry,
                such as <code>isRead</code> and <code>receivedDate</code>.

                Since the values of the RSS and Atom attributes are derived from data received
                from the server, they may be missing or incorrect. If you have the opportunity, use
                attributes generated by the Publication Subscription framework, as it is more reliable.
                For example, using <code>updatedDate</code> to find entries that have been modified 
                since a certain time would be unreliable. Use <code>receivedDate</code> instead. It 
                is not recommended that you subclass <code>PSEntry</code>.
    @attribute 	Framework /System/Library/Frameworks/PubSub.framework
    @seealso 	//apple_ref/doc/uid/TP40004945 Publication Subscription Programming Guide
*/

NS_DEPRECATED(10_5, 10_9, NA, NA)
@interface PSEntry : NSObject 
{
    @protected
    id _internal;
}


/*!
    @property   feed
    @abstract   The feed the receiver belongs to. (read-only)
*/
@property (readonly) PSFeed * feed;


/*! @property identifier 
    @abstract A string that uniquely identifies an entry. (read-only) 
    @discussion This identifier can be used as a key to map between <code>PSEntry</code> objects and your application's own data model objects.
    This identifier is generated internally by the Publication Subscription framework by combining the identifier of the feed with the 'most unique' attribute of the entry. You should not make any assumptions about its format or size, as they may change.
    (Although Atom defines a mandatory <id> element, it cannot be used for this purpose since the RSS equivalent (<guid>) is optional.  Thus, Publication Subscription uses its own mechanism for uniquely identifying entries. Clients can manually parse the <code>XMLRepresentation</code> output if they need the Atom <id> element or RSS <guid> element.) */
@property (readonly, retain) NSString * identifier;


/*! @property title 
    @abstract The entry's title. (read-only) 
    @discussion Corresponds to the <title> element in both Atom and RSS. */
@property (readonly, retain) NSString * title;


/*! @property rights 
    @abstract The entry's copyright information. (read-only) 
    @discussion Corresponds to the <rights> element in Atom.  There is no RSS equivalent. */
@property (readonly, retain) NSString * rights;


/*! @property content 
    @abstract The content of the entry. (read-only) 
    @discussion Corresponds to the <content> element in Atom and <description> in RSS. */
@property (readonly, retain) PSContent * content;


/*! @property summary 
    @abstract A string that contains the entry's summary. (read-only) 
    @discussion Corresponds to the <summary> element in Atom.  There is no RSS equivalent. */
@property (readonly, retain) PSContent * summary;


/*! @property dateUpdated 
    @abstract The date that the entry was last modified. (read-only) 
    @discussion The return value corresponds to the <updated> elements in Atom.  There is no RSS equivalent. To get the local date and time that the latest update was received by the user's machine, use the <code>localDateUpdated</code> method. */
@property (readonly, retain) NSDate * dateUpdated;


@property (readonly, retain) NSTimeZone * timeZoneUpdated;


/*! @property datePublished 
    @abstract The date that the entry was published. (read-only) 
    @discussion The return value corresponds to the <published> element in Atom and the <pubDate> element in RSS. */
@property (readonly, retain) NSDate * datePublished;


@property (readonly, retain) NSTimeZone * timeZonePublished;


/*! @property dateCreated 
    @abstract The date that the entry was created. (read-only) 
    @discussion The date corresponds to the <dc:created> element in Dublin Core (http://dublincore.org/).  There is no Atom nor RSS equivalent. When it exists, this date is set by either the author's blogging software or the server and is stored in the feed. It may be earlier than <code>datePublished</code> if the entry was not immediately published after being written. To get the local date and time when the entry was received by the user's machine, use the <code>locateDateCreated</code> method instead. */
@property (readonly, retain) NSDate * dateCreated;


@property (readonly, retain) NSTimeZone * timeZoneCreated;


/*! @property dateForDisplay 
    @abstract A guaranteed non-<code>nil</code> date for the entry, suitable for displaying or sorting. (read-only) 
    @discussion This returns the entry's <code>datePublished</code> if available, otherwise the <code>dateUpdated</code>; if neither appears in the feed, it falls back on the <code>localDateCreated</code>. Use this method if you need a guaranteed non-<code>nil</code> date, as in sorting or displaying in a table column. */
@property (readonly, retain) NSDate * dateForDisplay;


/*! @property baseURL 
    @abstract The base URL for resolving relative links.(read-only) 
    @discussion The returned URL corresponds to the xml:base attribute on an Atom <entry> element or an RSS <item> element. Publication Subscription resolves all parsed URLs to be absolute.  However, this is not possible for URLs embedded within an entry's content or summary.  If a client chooses to display content in HTML form, the base URL must be set for relative URLs to work.Note: Atom technically allows the xml:base attribute to appear as an attribute of the <content> or <summary> elements.  In practice, this seldom occurs.  A client may choose to parse these xml:base attributes manually via <code>XMLRepresentation</code>. */
@property (readonly, retain) NSURL * baseURL;


/*! @property alternateURL 
    @abstract The URL to an alternate version of the entry resource. (read-only) 
    @discussion Traditionally, the alternate URL corresponds to the HTML version of an entry. The URL is parsed from the <link rel="alternate"> element in Atom and the <link> element in RSS. This URL is often called a permalink. */
@property (readonly, retain) NSURL * alternateURL;


/*! @property authors 
    @abstract An array of author objects representing the entry's authors. (read-only) 
    @discussion The authors correspond to the <author> element in Atom and RSS. This method currently only supports a single author, the first one. */
@property (readonly, retain) NSArray * authors;


/*! @property contributors 
    @abstract An array of author objects that contains the entry's contributors. (read-only) 
    @discussion Corresponds to the <contributor> element in Atom.  There is no RSS equivalent. */
@property (readonly, retain) NSArray * contributors;


/*! @property enclosures 
    @abstract An array of enclosure objects of the enclosures of an entry. (read-only) 
    @discussion The enclosures correspond to the <link rel="enclosure"> element in Atom and the <enclosure> element in RSS. The order of the enclosure objects returned is undefined. */
@property (readonly, retain) NSArray * enclosures;


/*! @property current 
    @abstract A Boolean value indicating whether an entry still appears in its feed. (read-only) 
    @discussion Typically, a feed contains 10-15 entries at a time, so as a new entry is added, the oldest entry "falls off." If the property returns NO, the entry has 'fallen off the bottom' of the feed but is still in the PubSub Database. */
@property (readonly, getter=isCurrent) BOOL current;


/*! @property read 
    @abstract A Boolean value indicating whether or not the entry is read. 
    @discussion Read status of an article is shared among all applications using the Publication Subscription framework. By default, this method returns <code>NO</code>. */
@property (getter=isRead, setter=setRead:) BOOL read;


/*! @property flagged 
    @abstract A Boolean value indicating whether or not the entry is flagged. 
    @discussion Flagged status of an article is shared among all applications using the Publication Subscription framework. By default, this method returns <code>NO</code>. */
@property (getter=isFlagged, setter=setFlagged:) BOOL flagged;


/*! @property localDateCreated 
    @abstract The date when the entry was created in the local Publication Subscription database. (read-only) 
    @discussion  */
@property (readonly, retain) NSDate * localDateCreated;


/*! @property localDateUpdated 
    @abstract The date when the entry was updated in the local Publication Subscription database. (read-only) 
    @discussion  */
@property (readonly, retain) NSDate * localDateUpdated;



/*!
    @property   titleForDisplay
    @abstract   A string to display as the entry's title. (read-only)
    @discussion This property returns up to the first 100 characters 
                of the entry's summary, or content if there is no summary.
*/
@property (readonly) NSString * titleForDisplay;


/*!
    @property   authorsForDisplay
    @abstract   The authors of the entry as a string. (read-only)
    @discussion If there are multiple authors, they are comma-delimited.
*/
@property (readonly) NSString* authorsForDisplay;


/*!
    @property   XMLRepresentation
    @abstract   The raw XML entry. (read-only)
    @discussion The raw XML is parsed into a DOM tree, and the <entry> or <article> element
                is returned.
*/
@property (readonly) NSXMLElement * XMLRepresentation;


/*!
    @method     extensionXMLElementsUsingNamespace:
    @abstract   Returns an array of the extension XML elements that are outside of the RSS or Atom standards.
    @param      nameSpace  The extension XML elements you want to receive. Pass <code>nil</code> to get all extension XML elements, regardless of their namespace.
    @result     An array containing the extension XML elements requested. Make sure to pass a namespace and not a namespace prefix
                for the <code>nameSpace</code> parameter. For example, to retrieve the iTunes Podcast elements, use
                <code>extensionXMLElementsUsingNamespace:@"http://www.itunes.com/dtds/podcast-1.0.dtd"</code>, not
                <code>extensionXMLElementsUsingNamespace:@"itunes"</code>.
                
                This method attempts to communicate with the PubSubAgent process and causes the agent 
                to launch if it is not already running.  If PubSubAgent cannot be contacted, an exception 
                will be thrown with the name <code>PSException</code>.  To avoid problems, you should 
                always be prepared to catch an exception thrown by this method.
*/
- (NSArray *) extensionXMLElementsUsingNamespace:(NSString *)nameSpace;


@end

#endif
