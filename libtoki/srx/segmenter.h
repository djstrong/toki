#ifndef LIBTOKI_SRX_SEGMENTER_H
#define LIBTOKI_SRX_SEGMENTER_H

#include "rule.h"
#include <vector>
#include <map>

#include <unicode/regex.h>
#include <boost/regex/icu.hpp>
#include <boost/utility.hpp>

namespace Toki { namespace Srx {

	/**
	 * SRX Segmenter interface.
	 * SRX segmenters take SRX rules, compile them internally, and expose
	 * a method of calculating breaks within a given UnicodeString.
	 */
	class Segmenter : private boost::noncopyable
	{
	public:
		/**
		 * Constructor
		 */
		Segmenter();

		/// Destructor
		virtual ~Segmenter();

		/**
		 * Load rules -- rules are compiled by the derived classes since
		 * different derived classes might want a different compiled
		 * representation.
		 */
		virtual void load_rules(const std::vector<Rule>& rules) = 0;

		/**
		 * The main segmentation interface -- computing break positions in
		 * a UnicodeString. The entire string is taken into account, but only
		 * breaks between 'from' and 'to' are actually retained.
		 *
		 * This function returns void, use one of the accesor methods to get
		 * a representation of the found break positions, @see get_break_mask
		 * @see get_break_positions
		 *
		 * Derived classes should perform the actual matching here and fill the
		 * internal break map.
		 *
		 * @param str  The string to find segments in
		 * @param from Index of the beginning of the region in str where breaks
		 *             are to be remembered and returned/
		 * @param to   Index beyond the region in str, see from.
		 */
		virtual void compute_breaks(const UnicodeString& str, int from, int to) = 0;

		/**
		 * Break positions accesor -- returns a vector of true and false values
		 * for break positions in the from..to range used in the previous
		 * compute_breaks call.
		 */
		std::vector<bool> get_break_mask() const;

		/**
		 * Break positions accesor -- returns a (sorted) vector of the positions
		 * where breaks were detected in the previous compute_breaks call.
		 */
		std::vector<int> get_break_positions() const;

	protected:
		/// typedef for the internal break map
		typedef std::map<int, bool> break_map_t;

		/// break map
		break_map_t break_map_;

		/// length of the actually processed region in the last compute_breaks()
		int length_;

	};

	/**
	 * A segmenter using ICU regular expressions and a straightforward approach,
	 * matching all the rules in order and markong their match positions, which
	 * ends up getting us the break positions.
	 */
	class NaiveIcuSegmenter : public Segmenter
	{
	public:
		/// Constructor
		NaiveIcuSegmenter();

		/// Destructor
		~NaiveIcuSegmenter();

		/// Segmenter override.
		void load_rules(const std::vector<Rule>& rules);

		/// Segmenter override.
		virtual void compute_breaks(const UnicodeString& str, int from, int to);

		/// Accesor for the compiled rules
		const std::vector<CompiledRule>& get_compiled_rules() const {
			return crules_;
		}

	private:
		/// the compiled rules
		std::vector<CompiledRule> crules_;
	};

	/**
	 * A segmenter using Boost regular expressions and the same approach
	 * as the ICU counterpart, @see NaiveIcuSegmenter.
	 */
	class NaiveBoostSegmenter : public Segmenter
	{
	public:
		/// Constructor
		NaiveBoostSegmenter();

		/// Segmenter override.
		void load_rules(const std::vector<Rule>& rules);

		/// Segmenter override.
		virtual void compute_breaks(const UnicodeString& str, int from, int to);

	private:
		/// The compiled rules
		std::vector< std::pair<boost::u32regex, bool> > crules_;
	};

} /* end ns Srx */ } /* end ns Toki */

#endif // LIBTOKI_SRX_SEGMENTER_H
